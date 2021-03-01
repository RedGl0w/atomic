#include "list_atomic_cell.h"
#include <poincare/integer.h>
#include <poincare/number.h>
#include <escher/palette.h>

namespace Atomic {

ListAtomicCell::ListAtomicCell()
{
}

void ListAtomicCell::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), Palette::BackgroundApps);
  ctx->fillRect(m_atomRect(), Palette::AtomBackground);

  KDPoint symbolPoint(m_atomRect().x() + m_atomRect().width() / 2 - KDFont::LargeFont->stringSize(m_atom.symbol).width() / 2,
    m_atomRect().y() + m_atomRect().height() / 2 - KDFont::LargeFont->stringSize(m_atom.symbol).height() / 2);
  ctx->drawString(m_atom.symbol, symbolPoint, KDFont::LargeFont, Palette::AtomText, Palette::AtomBackground);

  char protons[4];
  Poincare::Integer(m_atom.num).serialize(protons, 4);
  KDPoint protonsPoint(m_atomRect().right() - KDFont::LargeFont->stringSize(protons).width() - k_padding,
    m_atomRect().top() + k_padding);
  ctx->drawString(protons, protonsPoint, KDFont::SmallFont, Palette::AtomText, Palette::AtomBackground);

  KDPoint massPoint(m_atomRect().bottomLeft().x() + k_padding, m_atomRect().bottomLeft().y() - KDFont::SmallFont->glyphSize().height());
  char mass[12];
  Poincare::Number::FloatNumber(m_atom.mass).serialize(mass, 12);
  mass[8] = 0;
  ctx->drawString(mass, massPoint, KDFont::SmallFont, Palette::AtomText, Palette::AtomBackground);

}

View * ListAtomicCell::subviewAtIndex(int index) {
  assert(false);
  return nullptr;
}

void ListAtomicCell::setAtom(AtomDef atom) {
  m_atom = atom;
  markRectAsDirty(bounds());
}

KDRect ListAtomicCell::m_atomRect() const {
  return KDRect((bounds().left() + (bounds().width()- k_width) / 2), bounds().top() + k_margin, k_width, bounds().height() - 2*k_margin);
}

void ListAtomicCell::layoutSubviews(bool force) {
}

}
