#include "app.h"
#include "apps/apps_container.h"
#include "atomic_icon.h"
#include "apps/i18n.h"
#include <assert.h>
#include <escher/app.h>

namespace Atomic {

I18n::Message App::Descriptor::name() {
  return I18n::Message::AtomicApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::AtomicAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::AtomicIcon;
}

App::Snapshot::Snapshot()
{
}

App * App::Snapshot::unpack(Container * container) {
  return new (container->currentAppBuffer()) App(this);
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

App::App(Snapshot * snapshot) : 
  ::App(snapshot, &m_controller, I18n::Message::Warning),
  m_controller(&m_modalViewController, snapshot)
{
}

}