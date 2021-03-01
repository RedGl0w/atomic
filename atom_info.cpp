#include "atom_info.h"
#include <poincare/integer.h>
#include <poincare/number.h>
#include <escher/palette.h>

namespace Atomic {

atomInfo::atomInfo() : 
  View(),
  m_atomName(KDFont::SmallFont)
{
}

void atomInfo::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(rect, Palette::BackgroundApps);
  char protons[4];
  char nucleons[4];
  char mass[12];
  Poincare::Integer(m_atom.num).serialize(protons, 4);
  Poincare::Integer(m_atom.neutrons + m_atom.num).serialize(nucleons, 4);
  Poincare::Number::FloatNumber(m_atom.mass).serialize(mass, 12, Poincare::Preferences::PrintFloatMode::Decimal, 12);
  KDPoint coordonates(bounds().topLeft());
  ctx->drawString(nucleons, coordonates, KDFont::SmallFont, Palette::AtomText, Palette::BackgroundApps);
  coordonates = KDPoint(coordonates.x(), coordonates.y() + 14);
  ctx->drawString(protons, coordonates, KDFont::SmallFont, Palette::AtomText, Palette::BackgroundApps);
  coordonates = KDPoint(bounds().left() + 23, bounds().top() + 6);
  ctx->drawString(m_atom.symbol, coordonates, KDFont::LargeFont, Palette::AtomText, Palette::BackgroundApps);
  coordonates = KDPoint(bounds().left() + 60, bounds().top() + 13);
  ctx->drawString(mass, coordonates, KDFont::SmallFont, Palette::AtomText, Palette::BackgroundApps);
}

int atomInfo::numberOfSubviews() const {
  return 1;
}

View * atomInfo::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_atomName;
}

void atomInfo::layoutSubviews(bool force) {
  m_atomName.setFrame(KDRect(KDPoint(60, 0), KDSize(bounds().width() - 60, KDFont::SmallFont->glyphSize().height())), force);
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
