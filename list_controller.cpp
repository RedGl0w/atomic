#include "list_controller.h"

namespace Atomic {

ListController::ListController(Responder * parentResponder) :
  ViewController(parentResponder),
  m_selectableTableView(this)
{
  for (int i = 0; i < k_numberOfRow; i++) {
    m_cells[i].setMessageFont(KDFont::LargeFont);
  }
}

bool ListController::handleEvent(Ion::Events::Event event) {
  return false;
}

View * ListController::view() {
  return &m_selectableTableView;
}

void ListController::didBecomeFirstResponder() {
  if (selectedRow() < 0) {
    selectCellAtLocation(0, 0);
  }
  Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

int ListController::numberOfRows() const {
  return k_numberOfRow;
}

KDCoordinate ListController::rowHeight(int j) {
  return Metric::ParameterCellHeight;
}

KDCoordinate ListController::cumulatedHeightFromIndex(int j) {
  KDCoordinate height = j * rowHeight(0);
  return height;
}

HighlightCell * ListController::reusableCell(int index, int type) {
  assert(index == 0 && type == 0);
  return &m_cells[index];
}

int ListController::reusableCellCount(int type) {
  assert(type == 0);
  return k_numberOfRow;
}

int ListController::typeAtLocation(int i, int j) {
  return 0;
}

void ListController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  switch (index) {
    case 0: {
      MessageTableCellWithMessage * myCell = (MessageTableCellWithMessage *)cell;
      myCell->setMessage(I18n::Message::AtomName);
      myCell->setAccessoryMessage(m_atom.name);
    }
  }
}

void ListController::viewWillAppear() {
  ViewController::viewWillAppear();
  m_selectableTableView.reloadData();
}

StackViewController * ListController::stackController() const {
  return (StackViewController *)parentResponder();
}

}
