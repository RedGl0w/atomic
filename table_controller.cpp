#include "table_controller.h"
#include "app.h"
#include "../apps_container.h"

extern "C" {
#include <assert.h>
}

namespace Atomic {

TableController::ContentView::ContentView(TableController * controller, SelectableTableViewDataSource * selectionDataSource) :
  m_selectableTableView(controller, controller, selectionDataSource, controller)
{
  m_selectableTableView.setVerticalCellOverlap(0);
  m_selectableTableView.setMargins(k_sideMargin, k_sideMargin, k_sideMargin, k_sideMargin);
  m_selectableTableView.setBackgroundColor(KDColorWhite);
}

SelectableTableView * TableController::ContentView::selectableTableView() {
  return &m_selectableTableView;
}

void TableController::ContentView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorWhite);
}

int TableController::ContentView::numberOfSubviews() const {
  return 2;
}

View * TableController::ContentView::subviewAtIndex(int index) {
  switch(index) {
    case 0:
      return &m_selectableTableView;
    case 1:
      return &m_ok;
    default:
      assert(false);
      return nullptr;
  }
}

void TableController::ContentView::layoutSubviews(bool force) {
  m_selectableTableView.setFrame(bounds(), force);
  m_ok.setFrame(KDRect(295,200, m_ok.minimalSizeForOptimalDisplay()), force);
}

TableController::TableController(Responder * parentResponder, SelectableTableViewDataSource * selectionDataSource) :
  ViewController(parentResponder),
  m_view(this, selectionDataSource)
{
}

bool TableController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Right && m_cursor < (sizeof(atomsdefs) / sizeof(AtomDef) - 1)) {
    AtomDef atom = atomsdefs[++m_cursor];
    selectCell(atom.x,atom.y);
    return true;
  }
  if (event == Ion::Events::Left && m_cursor > 0) {
    AtomDef atom = atomsdefs[--m_cursor];
    selectCell(atom.x,atom.y);
    return true;
  }
  // FIXME One keypress after Up/Down with Left/Right, this is glitchy
  if (event == Ion::Events::Up) {
    int row = selectionDataSource()->selectedRow();
    int column = selectionDataSource()->selectedColumn();
    if (row > 0) {
      if (row == 8) {
        row--;
      }
      for(AtomDef atom : atomsdefs) {
        if (atom.x == column && atom.y == row-1) {
          selectCell(atom.x, atom.y);
          return true;
        }
      }
    }
    return true;
  }
  if (event == Ion::Events::Down) {
    int row = selectionDataSource()->selectedRow();
    int column = selectionDataSource()->selectedColumn();
    if (row < 9) {
      if (row == 6) {row++;}
      for(AtomDef atom : atomsdefs) {
        if (atom.x == column && atom.y == row+1) {
          selectCell(atom.x, atom.y);
          return true;
        }
      }
    }
  }
  return false;
}

void TableController::didBecomeFirstResponder() {
  if (selectionDataSource()->selectedRow() == -1) {
    selectCell(0,0);
  }
}

View * TableController::view() {
  return &m_view;
}

int TableController::numberOfRows() const {
  return ((k_maxNumberOfCells - 1) / k_numberOfColumns) + 1;
}

int TableController::numberOfColumns() const {
  return k_numberOfColumns;
}

KDCoordinate TableController::cellHeight() {
  return k_cellHeight;
}

KDCoordinate TableController::cellWidth() {
  return k_cellWidth;
}

HighlightCell * TableController::reusableCell(int index) {
  assert(index < k_maxNumberOfCells);
  return &m_cells[index];
}

int TableController::reusableCellCount() const {
  return k_maxNumberOfCells;
}

void TableController::willDisplayCellAtLocation(HighlightCell * cell, int i, int j) {
  AtomicCell* c = static_cast<AtomicCell*>(cell);
  for(AtomDef atom : atomsdefs) {
    if(atom.x == i && atom.y == j) {
      c->setVisible(true);
      c->setAtom(atom);
      return;
    }
  }
  c->setVisible(false);
}

SelectableTableViewDataSource * TableController::selectionDataSource() const {
  return App::app()->snapshot();
}

void TableController::selectCell(int i, int j) {
  m_view.selectableTableView()->selectCellAtLocation(i,j,false);
}

}
