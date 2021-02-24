#include "list_atomic_cell.h"

namespace Atomic {

void ListAtomicCell::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorBlack);
}

}
