#ifndef ATOMIC_LIST_CONTROLLER_H
#define ATOMIC_LIST_CONTROLLER_H

#include <escher.h>
#include <apps/i18n.h>

namespace Atomic {

class ListController : public ViewController {
public:
  ListController(Responder * parentResponder);
  View * view() { return &m_view; }
  const char * title() override { return "WoW"; }
  bool handleEvent(Ion::Events::Event event) override;
private:
  class innerView : public View {
  public:
    void drawRect(KDContext * ctx, KDRect rect);
  };
  innerView m_view;
};

}

#endif

