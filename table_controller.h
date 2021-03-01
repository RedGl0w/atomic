#ifndef ATOMIC_TABLE_CONTROLLER_H
#define ATOMIC_TABLE_CONTROLLER_H

#include <escher.h>
#include "../shared/ok_view.h"
#include "atomic_cell.h"
#include "atom_info.h"
#include "table_lines_view.h"
#include "atoms.h"
#include "list_controller.h"

namespace Atomic {

class TableController : public ViewController, public SimpleTableViewDataSource, public SelectableTableViewDelegate {
public:
  TableController(Responder * parentResponder, SelectableTableViewDataSource * selectionDataSource);

  View * view() override;

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  TELEMETRY_ID("");

  int numberOfRows() const override;
  int numberOfColumns() const override;
  KDCoordinate cellHeight() override;
  KDCoordinate cellWidth() override;
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() const override;
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;
private:
  SelectableTableViewDataSource * selectionDataSource() const;
  void setSelection(AtomDef atom);
  StackViewController * stackController() const;
  class ContentView : public View {
  public:
    ContentView(TableController * controller, SelectableTableViewDataSource * selectionDataSource);
    SelectableTableView * selectableTableView();
    void drawRect(KDContext * ctx, KDRect rect) const override;
    void setAtom(AtomDef atom) { m_info.setAtom(atom); }
  private:
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    void layoutSubviews(bool force = false) override;
    SelectableTableView m_selectableTableView;
    Shared::OkView m_ok;
    atomInfo m_info;
    tableLinesView m_lines;
  };
  static constexpr KDCoordinate k_sideMargin = 6;
  static constexpr KDCoordinate k_indicatorMargin = 61;
  static constexpr int k_numberOfColumns = 18;
  static constexpr int k_maxNumberOfCells = 180;
  static constexpr int k_cellHeight = 17;
  static constexpr int k_cellWidth = 17;
  int m_position;
  ContentView m_view;
  AtomicCell m_cells[k_maxNumberOfCells];
  int m_cursor = 0;
  ListController m_list;
};

}

#endif
