#ifndef ATOMIC_CELL_H
#define ATOMIC_CELL_H

#include <escher.h>
#include "atoms.h"

namespace Atomic {

class AtomicCell : public HighlightCell {
public:
  AtomicCell();
  void drawRect(KDContext * ctx, KDRect rect) const override;

  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews(bool force = false) override;

  void setVisible(bool visible);
  void setAtom(AtomDef atom);
  void reloadCell() override;
private:
  static constexpr KDCoordinate k_iconMargin = 22;
  static constexpr KDCoordinate k_iconWidth = 55;
  static constexpr KDCoordinate k_iconHeight = 56;
  static constexpr KDCoordinate k_nameWidthMargin = 4;
  static constexpr KDCoordinate k_nameHeightMargin = 1;
  bool m_visible;
  AtomDef m_atom;
  KDColor colorForType(AtomType type) const;
};

}

#endif
