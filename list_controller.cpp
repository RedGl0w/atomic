#include "list_controller.h"

namespace Atomic {

ListController::ListController(Responder * parentResponder) :
  ViewController(parentResponder)
{}

void ListController::innerView::drawRect(KDContext * ctx, KDRect rect) {
  ctx->fillRect(rect, KDColorBlack);
}

bool ListController::handleEvent(Ion::Events::Event event) {
  return false;
}

}
