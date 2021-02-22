#include "atom_info.h"
#include <poincare/integer.h>

namespace Atomic {

atomInfo::atomInfo() : 
  View()
{
}

void atomInfo::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(rect, KDColorWhite);
  char protons[4];
  char nucleons[4];
  Poincare::Integer(m_atom.num).serialize(protons, 4);
  Poincare::Integer(m_atom.neutrons + m_atom.num).serialize(nucleons, 4);
  ctx->drawString(protons, bounds().topLeft(), KDFont::SmallFont);
}

void atomInfo::setAtom(AtomDef atom) {
  markRectAsDirty(bounds());
  m_atom = atom;
}

KDSize atomInfo::minimalSizeForOptimalDisplay() const {
  return KDSize(120, 40);
}

}
