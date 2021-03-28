#ifndef ATOMIC_LIST_CONTROLLER_H
#define ATOMIC_LIST_CONTROLLER_H

#include <escher.h>
#include <apps/i18n.h>
#include "atoms.h"
#include "list_atomic_cell.h"
#include "message_table_cell_with_expression_with_copy.h"

namespace Atomic {

class ListController : public StackViewController, public ListViewDataSource, public SelectableTableViewDataSource, public SelectableTableViewDelegate {
public:
  ListController(Responder * parentResponder);
  void didBecomeFirstResponder() override;
  int numberOfRows() const override;
  KDCoordinate rowHeight(int j) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  bool handleEvent(Ion::Events::Event event) override;

  void setAtom(AtomDef atom);

  void tableViewDidChangeSelection(SelectableTableView * t, int previousSelectedCellX, int previousSelectedCellY, bool withinTemporarySelection) override;

private:
  class InnerView : public ViewController {
  public:
    InnerView(ListController * dataSource);
    const char * title() override { return I18n::translate(m_atom.name); }
    View * view() override { return &m_selectableTableView; }
    void didBecomeFirstResponder() override;
    SelectableTableView * selectableTableView() { return &m_selectableTableView; }
    void setAtom(AtomDef atom);
  private:
    SelectableTableView m_selectableTableView;
    AtomDef m_atom;
  };

  class Electronical {
  public :
    static Poincare::Layout createElectronical(AtomDef atom);
  private:
    static Poincare::Layout computeLayer(CodePoint c, int subLayoutNumber, int number);
    struct rowsSubLayers {
      bool s;
      int sNumber;
      bool f;
      int fNumber;
      bool d;
      int dNumber;
      bool p;
      int pNumber;
    };
    struct exceptionStruct {
      int num;
      bool s;
      int sContent;
      bool f;
      int fContent;
      bool d;
      int dContent;
      bool p;
      int pContent;
    };
    const static rowsSubLayers rows[];
    const static exceptionStruct exceptions[18];
    
  };

  constexpr static int k_atomicCellRowHeight = 110;
  constexpr static int k_classicalRowHeight = 30;

  ListAtomicCell m_atomicCell;
  constexpr static int k_numberOfCellsWithBuffer = 2;
  MessageTableCellWithBuffer m_cellsWithBuffer[k_numberOfCellsWithBuffer];
  constexpr static int k_numberOfCellsWithExpression = 5;
  MessageTableCellWithExpressionWithCopy m_cellsWithExpression[k_numberOfCellsWithExpression];
  constexpr static int k_numberOfRow = 1 + k_numberOfCellsWithBuffer + k_numberOfCellsWithExpression;
  InnerView m_innerView;
  AtomDef m_atom;
  Responder* m_parent;
};

}

#endif

