#include "table_controller.h"
#include "app.h"
#include "../apps_container.h"
#include <escher/palette.h>

extern "C" {
#include <assert.h>
}

namespace Atomic {

TableController::ContentView::ContentView(TableController * controller, SelectableTableViewDataSource * selectionDataSource) :
  m_selectableTableView(controller, controller, selectionDataSource, controller)
{
  m_selectableTableView.setVerticalCellOverlap(0);
  m_selectableTableView.setMargins(k_sideMargin, k_sideMargin, k_sideMargin, k_sideMargin);
  m_selectableTableView.setBackgroundColor(Palette::BackgroundApps);
}

SelectableTableView * TableController::ContentView::selectableTableView() {
  return &m_selectableTableView;
}

void TableController::ContentView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), Palette::BackgroundApps);
}

int TableController::ContentView::numberOfSubviews() const {
  return 4;
}

View * TableController::ContentView::subviewAtIndex(int index) {
  switch(index) {
    case 0:
      return &m_selectableTableView;
    case 1:
      return &m_ok;
    case 2:
      return &m_info;
    case 3:
      return &m_lines;
    default:
      assert(false);
      return nullptr;
  }
}

void TableController::ContentView::layoutSubviews(bool force) {
  m_selectableTableView.setFrame(bounds(), force);
  m_ok.setFrame(KDRect(295,200, m_ok.minimalSizeForOptimalDisplay()), force);
  m_info.setFrame(KDRect(KDPoint(48,15),m_info.minimalSizeForOptimalDisplay()), force);
  m_lines.setFrame(KDRect(KDPoint(48, 99), m_lines.minimalSizeForOptimalDisplay()), force);
}

TableController::TableController(Responder * parentResponder, SelectableTableViewDataSource * selectionDataSource) :
  ViewController(parentResponder),
  m_view(this, selectionDataSource),
  m_list(this)
{
}

bool TableController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Right && m_cursor < static_cast<int>(sizeof(atomsdefs) / sizeof(AtomDef) - 1)) {
    AtomDef atom = atomsdefs[++m_cursor];
    setSelection(atom);
    return true;
  }
  if (event == Ion::Events::Left && m_cursor > 0) {
    AtomDef atom = atomsdefs[--m_cursor];
    setSelection(atom);
    return true;
  }
  if (event == Ion::Events::Up) {
    int row = selectionDataSource()->selectedRow();
    int column = selectionDataSource()->selectedColumn();
    if (row > 0) {
      if (row == 8) {
        row--;
      }
      for(size_t i = 0; i < (sizeof(atomsdefs) / sizeof(AtomDef)); i++) {
        AtomDef atom = atomsdefs[i];
        if (atom.x == column && atom.y == row-1) {
          m_cursor = i;
          setSelection(atom);
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
      for(size_t i = 0; i < (sizeof(atomsdefs) / sizeof(AtomDef)); i++) {
        AtomDef atom = atomsdefs[i];
        if (atom.x == column && atom.y == row+1) {
          m_cursor = i;
          setSelection(atom);
          return true;
        }
      }
    }
  }
  if (event == Ion::Events::OK || event == Ion::Events::EXE) {
    Container::activeApp()->displayModalViewController(&m_list, 0.f, 0.f, Metric::CommonTopMargin, Metric::PopUpLeftMargin, 0, Metric::PopUpRightMargin);
    return true;
  }
  return false;
}

void TableController::didBecomeFirstResponder() {
  if (selectionDataSource()->selectedRow() == -1) {
    setSelection(atomsdefs[0]);
  } else {
    setSelection(atomsdefs[m_cursor]);
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

void TableController::setSelection(AtomDef atom) {
  m_view.selectableTableView()->selectCellAtLocation(atom.x,atom.y,false);
  m_view.setAtom(atom);
  m_list.setAtom(atomsdefs[m_cursor]);
}

StackViewController * TableController::stackController() const {
  return (StackViewController *)parentResponder();
}

}
