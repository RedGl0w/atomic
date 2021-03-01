#include "table_lines_view.h"
#include <escher/palette.h>

namespace Atomic {

tableLinesView::tableLinesView() :
  View()
{
}

void tableLinesView::drawRect(KDContext * ctx, KDRect rect) const {
  KDColor color = Palette::AtomTableLines;
  ctx->fillRect(KDRect(bounds().topLeft(), KDSize(2, 69)), color);
  ctx->fillRect(KDRect(KDPoint(bounds().left(), 50), KDSize(9, 2)), color);
  ctx->fillRect(KDRect(KDPoint(bounds().left(), 67), KDSize(9, 2)), color);
}

KDSize tableLinesView::minimalSizeForOptimalDisplay() const {
  return KDSize(9, 69);
}

}
