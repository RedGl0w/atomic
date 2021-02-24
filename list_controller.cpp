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

void ListController::InnerView::didBecomeFirstResponder() {
  m_selectableTableView.reloadData();
  m_selectableTableView.selectCellAtLocation(0,1);
}

ListController::ListController(Responder * parentResponder) :
  StackViewController(parentResponder, &m_innerView, Palette::PurpleBright, Palette::PurpleDark),
  m_innerView(this)
{
  for (int i = 0; i < k_numberOfCellsWithBuffer; i++) {
    m_cellsWithBuffer[i].setMessageFont(KDFont::LargeFont);
  }
  for (int i = 0; i < k_numberOfCellsWithExpression; i++) {
    m_cellsWithExpression[i].setMessageFont(KDFont::LargeFont);
  }
}

bool ListController::handleEvent(Ion::Events::Event event) {
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
    default: {
      assert(false);
    }
  }
}

}
