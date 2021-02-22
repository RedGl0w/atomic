#ifndef ATOMIC_TABLE_LINES_VIEW_H
#define ATOMIC_TABLE_LINES_VIEW_H

#include <escher.h>

namespace Atomic {

class tableLinesView : public View {
public:
  tableLinesView();
  void drawRect(KDContext * ctx, KDRect rect) const override;
  KDSize minimalSizeForOptimalDisplay() const override;
};

}

#endif
