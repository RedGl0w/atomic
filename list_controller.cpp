#include "list_controller.h"
#include <poincare_layouts.h>
#include <poincare_nodes.h>
#include <poincare/float.h>

namespace Atomic {

ListController::InnerView::InnerView(ListController * dataSource) :
  ViewController(dataSource),
  m_selectableTableView(this, dataSource, dataSource, dataSource)
{
  m_selectableTableView.setMargins(0);
  m_selectableTableView.setDecoratorType(ScrollView::Decorator::Type::None);
  m_selectableTableView.setMargins(0,0,0,0);
}

void ListController::InnerView::setAtom(AtomDef atom) {
 m_atom = atom;
 m_selectableTableView.reloadData(false);
}

void ListController::InnerView::didBecomeFirstResponder() {
  m_selectableTableView.reloadData();
  m_selectableTableView.selectCellAtLocation(0,1);
}

ListController::ListController(Responder * parentResponder) :
  StackViewController(parentResponder, &m_innerView, Palette::PurpleBright, Palette::PurpleDark),
  m_innerView(this),
  m_parent(parentResponder)
{
  for (int i = 0; i < k_numberOfCellsWithBuffer; i++) {
    m_cellsWithBuffer[i].setMessageFont(KDFont::LargeFont);
  }
  for (int i = 0; i < k_numberOfCellsWithExpression; i++) {
    m_cellsWithExpression[i].setMessageFont(KDFont::LargeFont);
  }
}

bool ListController::handleEvent(Ion::Events::Event event) {
  
  if (event == Ion::Events::Right || event == Ion::Events::Left) {
    return m_parent->handleEvent(event);
  }
  
  return false;
}

void ListController::didBecomeFirstResponder() {
  selectCellAtLocation(0, 0);
  Container::activeApp()->setFirstResponder(&m_innerView);
}

int ListController::numberOfRows() const {
  return k_numberOfRow;
}

KDCoordinate ListController::rowHeight(int j) {
  if (j == 0) {
    return k_atomicCellRowHeight;
  }
  if (j == 7) {
    return 35;
  }
  return k_classicalRowHeight;
}


HighlightCell * ListController::reusableCell(int index, int type) {
  assert(index < k_numberOfRow);
  switch (type) {
    case 0:
      {
        assert(index == 0);
        return &m_atomicCell;
      }
    case 1:
      {
        return &m_cellsWithBuffer[index];
      }
    case 2:
      {
        return &m_cellsWithExpression[index];
      }
    default:
      {
        assert(false);
        return nullptr;
      }
  }
}

void ListController::tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY, bool withinTemporarySelection) {
  if (withinTemporarySelection) {
    return;
  }
  // Forbid selecting ListAtomicCell
  if (t->selectedRow() == 0) {
    t->selectCellAtLocation(0, 1);
  }
  /* But scroll to the top when we select the first
   * cell in order display the ListAtomicCell. */
  if (t->selectedRow() == 1) {
    t->scrollToCell(0, 0);
  }
}

int ListController::reusableCellCount(int type) {
  assert(type == 0);
  return k_numberOfRow;
}

int ListController::typeAtLocation(int i, int j) {
  if (j == 0) {
    return 0;
  } else if (j == 1 || j == 4) {
    return 1;
  } else {
    return 2;
  }
}

void ListController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  switch (index) {
    case 0 : {
      m_atomicCell.setAtom(m_atom);
      return;
    }
    case 1: {
      MessageTableCellWithBuffer * myCell = (MessageTableCellWithBuffer *)cell;
      myCell->setMessage(I18n::Message::AtomSymbol);
      myCell->setAccessoryText(m_atom.symbol);
      myCell->setAccessoryFont(KDFont::SmallFont);
      return;
    }
    case 2: {
      MessageTableCellWithExpression * myCell = (MessageTableCellWithExpression *)cell;
      myCell->setMessage(I18n::Message::AtomNum);
      myCell->setLayout(Poincare::Integer(m_atom.num).createLayout());
      return;
    }
    case 3: {
      MessageTableCellWithExpression * myCell = (MessageTableCellWithExpression *)cell;
      myCell->setMessage(I18n::Message::AtomNeutrons);
      myCell->setLayout(Poincare::Integer(m_atom.neutrons).createLayout());
      return;
    }
    case 4: {
      MessageTableCellWithBuffer * myCell = (MessageTableCellWithBuffer *)cell;
      myCell->setMessage(I18n::Message::AtomTypes);
      myCell->setAccessoryText(I18n::translate(AtomicI18nForType[static_cast<int>(m_atom.type)]));
      myCell->setAccessoryFont(KDFont::SmallFont);
      return;
    }
    case 5: {
      MessageTableCellWithExpression * myCell = (MessageTableCellWithExpression *)cell;
      myCell->setMessage(I18n::Message::AtomMass);
      myCell->setLayout(Poincare::FloatNode<double>(m_atom.mass).createLayout(Poincare::Preferences::PrintFloatMode::Decimal, 7));
      return;
    }
    case 6: {
      MessageTableCellWithExpression * myCell = (MessageTableCellWithExpression *)cell;
      myCell->setMessage(I18n::Message::AtomElectroneg);
      myCell->setLayout(Poincare::FloatNode<double>(m_atom.electroneg).createLayout(Poincare::Preferences::PrintFloatMode::Decimal, 5));
      return;
    }
    case 7: {
      MessageTableCellWithExpression * myCell = (MessageTableCellWithExpression *)cell;
      myCell->setMessage(I18n::Message::AtomNum);
      myCell->setLayout(Electronical::createElectronical(m_atom));
      return;
    }
    default: {
      assert(false);
    }
  }
}

Poincare::Layout ListController::Electronical::createElectronical(AtomDef atom) {
  Poincare::Layout layouts[6];

  int y = (atom.y < 8) ?  atom.y : atom.y - 3;

  if (atom.y > 0) {
    char previousAtom[5] = {'[', ' ', ' ', ']', '\0'};
    for (AtomDef a : atomsdefs) {
      int ay = (a.y < 8) ? a.y : a.y - 3;
      if (ay == y - 1 && a.x == 17) {
        memcpy(&previousAtom[1], a.symbol, 2);
      }
    };
    layouts[0] = Poincare::LayoutHelper::String(previousAtom, strlen(previousAtom));
  }

  int indexAtRow = -1;
  for (AtomDef a : atomsdefs) {
    int ay = (a.y < 8) ? a.y : a.y - 3;
    if (ay == y) {
      indexAtRow = atom.num - a.num + 1;
      break;
    }
  }
  assert(indexAtRow != -1);

  int s=0, f=0, d=0, p=0;
  Electronical::rowsSubLayers row = Electronical::rows[y];
  bool sEnabled = row.s, fEnabled = row.f, dEnabled = row.d, pEnabled = row.p;
  int toOrder = indexAtRow;
  for (int i = 0; i < indexAtRow; i++) {
    if (sEnabled && s < 2) {
      s++;
      toOrder--;
    } else if (fEnabled && f < 14) {
      f++;
      toOrder--;
    } else if (dEnabled && d < 10) {
      d++;
      toOrder--;
    } else if (pEnabled && p < 6) {
      p++;
      toOrder--;
    }
  }
  assert(toOrder == 0);

  int index = (layouts[0].isUninitialized()) ? 0 : 1; 
  // FIXME The 4 conditionnal blocs following are crashing with the 2 "additional" rows (Lanthanide and actinide)
  if (s != 0) {
    layouts[index] = computeLayer('s', row.sNumber, s);
    index++;
  }
  if (f != 0) {
    layouts[index] = computeLayer('f', row.fNumber, f);
    index++;
  }
  if (d != 0) {
    layouts[index] = computeLayer('d', row.dNumber, d);
    index++;
  }
  if (p != 0) {
    layouts[index] = computeLayer('p', row.pNumber, p);
    index++;
  }

  Poincare::HorizontalLayout result = Poincare::HorizontalLayout::Builder(); // FIXME The display is totally broken
  for(int i = 0; i < 5; i++) {
    if(layouts[i].isUninitialized()) {
      break;
    }
    result.addChildAtIndex(layouts[i], i, i, nullptr);
  }

  return result;
}

Poincare::Layout ListController::Electronical::computeLayer(CodePoint c, int subLayoutNumber, int number) {
  return Poincare::HorizontalLayout::Builder(
      Poincare::Rational::Builder(subLayoutNumber).createLayout(Poincare::Preferences::PrintFloatMode::Decimal, 7),
      Poincare::CodePointLayout::Builder(c),
      Poincare::VerticalOffsetLayout::Builder(
        Poincare::Rational::Builder(number).createLayout(Poincare::Preferences::PrintFloatMode::Decimal, 7),
        Poincare::VerticalOffsetLayoutNode::Position::Superscript)
    );
}

const ListController::Electronical::rowsSubLayers ListController::Electronical::rows[] = {
  { true,  1,  false, -1,  false, -1,  false, -1 }, // 1s²
  { true,  2,  false, -1,  false, -1,   true,  2 }, // 2s² 2p⁶
  { true,  3,  false, -1,  false, -1,   true,  3 }, // 3s² 3p⁶
  { true,  4,  false, -1,   true,  3,   true,  4 }, // 4s² 3d¹⁰ 4p⁶
  { true,  5,  false, -1,   true,  4,   true,  5 }, // 5s² 4d¹⁰ 5p⁶
  { true,  6,  true,   4,   true,  5,   true,  6 }, // 6s² 4f¹⁴ 5d¹⁰ 6p⁶
  { true,  7,  true,   5,   true,  6,   true,  7 }, // 6s² 4f¹⁴ 5d¹⁰ 6p⁶
};

}
