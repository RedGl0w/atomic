#ifndef ATOMIC_LIST_ATOMIC_CELL_H
#define ATOMIC_LIST_ATOMIC_CELL_H

#include <escher/bordered.h>
#include <escher/highlight_cell.h>

namespace Atomic {

class ListAtomicCell : public Bordered, public HighlightCell {
public:
  void setHighlighted(bool highlight) override { return; }
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  /* int numberOfSubviews() const override { return 0; }
  View * subviewAtIndex(int index) override { assert(false); return nullptr; }
  void layoutSubviews(bool force = false) override; */
};

}

#endif

