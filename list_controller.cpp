#include "list_controller.h"
#include <poincare_layouts.h>
#include <poincare_nodes.h>

namespace Atomic {

ListController::InnerView::InnerView(ListController * dataSource) :
  ViewController(dataSource),
  m_selectableTableView(this, dataSource, dataSource, nullptr)
{
  m_selectableTableView.setMargins(0);
  m_selectableTableView.setDecoratorType(ScrollView::Decorator::Type::None);
  m_selectableTableView.setMargins(5,5,5,5);
}

void ListController::InnerView::didBecomeFirstResponder() {
  m_selectableTableView.reloadData();
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
  if (selectedRow() < 0) {
    selectCellAtLocation(0, 0);
  }
  Container::activeApp()->setFirstResponder(&m_innerView);
}

int ListController::numberOfRows() const {
  return k_numberOfRow;
}

KDCoordinate ListController::rowHeight(int j) {
  return 25;
}

KDCoordinate ListController::cumulatedHeightFromIndex(int j) {
  KDCoordinate height = j * rowHeight(0);
  return height;
}

HighlightCell * ListController::reusableCell(int index, int type) {
  assert(index < k_numberOfRow);
  switch (type) {
    case 0:
      {
        return &m_cellsWithBuffer[index];
      }
    case 1:
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

int ListController::reusableCellCount(int type) {
  assert(type == 0);
  return k_numberOfRow;
}

int ListController::typeAtLocation(int i, int j) {
  if (j < k_numberOfCellsWithBuffer) {
    return 0;
  } else {
    return 1;
  }
}

void ListController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  switch (index) {
    case 0: {
      MessageTableCellWithBuffer * myCell = (MessageTableCellWithBuffer *)cell;
      myCell->setMessage(I18n::Message::AtomName);
      myCell->setAccessoryText(I18n::translate(m_atom.name)); // FIXME We shouldn't use here an I18n::translate
      myCell->setAccessoryFont(KDFont::SmallFont);
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
  }
}

}
