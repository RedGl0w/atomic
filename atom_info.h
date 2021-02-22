#ifndef ATOMIC_INFO_H
#define ATOMIC_INFO_H

#include <escher.h>
#include "atoms.h"

namespace Atomic {

class atomInfo : public View {
public:
  atomInfo();
  void drawRect(KDContext * ctx, KDRect rect) const override;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews(bool force = false) override;
  KDSize minimalSizeForOptimalDisplay() const override;
  void setAtom(AtomDef atom);
private:
  AtomDef m_atom;
  MessageTextView m_atomName;
};

}

#endif
