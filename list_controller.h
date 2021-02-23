#ifndef ATOMIC_LIST_CONTROLLER_H
#define ATOMIC_LIST_CONTROLLER_H

#include <escher.h>
#include <apps/i18n.h>
#include "atoms.h"

namespace Atomic {

class ListController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource {
public:
  ListController(Responder * parentResponder);

  View * view() override;
  void didBecomeFirstResponder() override;
  int numberOfRows() const override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  void viewWillAppear() override;

  const char * title() override { return I18n::translate(m_atom.name); }

  bool handleEvent(Ion::Events::Event event) override;

  void setAtom(AtomDef atom) { m_atom = atom; }

private:
  constexpr static int k_numberOfRow = 1;
  StackViewController * stackController() const;
  MessageTableCellWithMessage m_cells[k_numberOfRow];
  SelectableTableView m_selectableTableView;
  AtomDef m_atom;
};

}

#endif

