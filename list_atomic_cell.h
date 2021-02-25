#ifndef ATOMIC_LIST_ATOMIC_CELL_H
#define ATOMIC_LIST_ATOMIC_CELL_H

#include <escher/bordered.h>
#include <escher/highlight_cell.h>
#include "atoms.h"

namespace Atomic {

class ListAtomicCell : public Bordered, public HighlightCell {
public:
  ListAtomicCell();
  void setHighlighted(bool highlight) override { return; }
  void drawRect(KDContext * ctx, KDRect rect) const override;
  void setAtom(AtomDef atom);
private:
  constexpr static int k_width = 60;
  constexpr static int k_margin = 10;
  constexpr static int k_padding = 3;
  int numberOfSubviews() const override { return 0; }
  View * subviewAtIndex(int index) override;
  void layoutSubviews(bool force = false) override;
  KDRect m_atomRect() const;
  AtomDef m_atom;
};

}

#endif

