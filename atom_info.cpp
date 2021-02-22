#include "atom_info.h"
#include <poincare/integer.h>

namespace Atomic {

atomInfo::atomInfo() : 
  View(),
  m_atomName(KDFont::SmallFont)
{
}

void atomInfo::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(rect, KDColorWhite);
  char protons[4];
  char nucleons[4];
  Poincare::Integer(m_atom.num).serialize(protons, 4);
  Poincare::Integer(m_atom.neutrons + m_atom.num).serialize(nucleons, 4);
  KDPoint coordonates(bounds().topLeft());
  ctx->drawString(nucleons, coordonates, KDFont::SmallFont);
  coordonates = KDPoint(coordonates.x(), coordonates.y() + 14);
  ctx->drawString(protons, coordonates, KDFont::SmallFont);
  coordonates = KDPoint(bounds().left() + 23, bounds().top() + 6);
  ctx->drawString(m_atom.symbol, coordonates);
}

int atomInfo::numberOfSubviews() const {
  return 1;
}

View * atomInfo::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_atomName;
}

void atomInfo::layoutSubviews(bool force) {
  m_atomName.setFrame(KDRect(KDPoint(60, 10), KDSize(bounds().width() - 60, bounds().height() - 10)), force);
}

void atomInfo::setAtom(AtomDef atom) {
  m_atom = atom;
  m_atomName.setMessage(atom.name);
  markRectAsDirty(bounds());
}

KDSize atomInfo::minimalSizeForOptimalDisplay() const {
  return KDSize(150, 40);
}

}
