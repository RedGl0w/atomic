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
  if (event == Ion::Events::Right && selectionDataSource()->selectedRow() < numberOfRows() - 1) {
    return m_view.selectableTableView()->selectCellAtLocation(0, selectionDataSource()->selectedRow() + 1);
  }
  if (event == Ion::Events::Left && selectionDataSource()->selectedRow() > 0) {
    return m_view.selectableTableView()->selectCellAtLocation(numberOfColumns() - 1, selectionDataSource()->selectedRow() - 1);
  }
  return false;
}

void TableController::didBecomeFirstResponder() {
  if (selectionDataSource()->selectedRow() == -1) {
    selectionDataSource()->selectCellAtLocation(0, 0);
  }
  Container::activeApp()->setFirstResponder(m_view.selectableTableView());
}

void TableController::tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY, bool withinTemporarySelection) {
  int x = t->selectedColumn();
  int y = t->selectedRow();
  //std::cout << previousSelectedCellX << " " << previousSelectedCellY << " " << x << " " << y << std::endl;
  // FIXME
  // The selection is totally broken :/
  m_cells[0].reloadCell(); // Some hack to redraw the view
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
  if(j == 7) {
    c->setVisible(false); // Row 7 is empty
    return;
  }
  int y = (j < 7) ? j : j-1; // But it atomsDef row 7 is not empty
  for(AtomDef atom : atomsdefs) {
    if(atom.x == i && atom.y == y) {
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

}
