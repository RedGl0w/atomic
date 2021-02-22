#ifndef ATOMIC_APP_H
#define ATOMIC_APP_H

#include "../shared/shared_app.h"
#include "table_controller.h"
#include <escher.h>

namespace Atomic {

class App : public ::App {
public:
  class Descriptor : public ::App::Descriptor {
  public:
    I18n::Message name() override;
    I18n::Message upperName() override;
    const Image * icon() override;
  };
  class Snapshot : public ::SharedApp::Snapshot, public SelectableTableViewDataSource {
  public:
    Snapshot();
    App * unpack(Container * container) override;
    Descriptor * descriptor() override;
  };
  static App * app() {
    return static_cast<App *>(Container::activeApp());
  }
  Snapshot * snapshot() const {
    return static_cast<Snapshot *>(::App::snapshot());
  }
private:
  App(Snapshot * snapshot);
  TableController m_controller;
  StackViewController m_stackViewController;
};

}

#endif