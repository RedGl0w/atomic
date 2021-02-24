#include "list_atomic_cell.h"
#include <iostream>
#include <poincare/integer.h>

namespace Atomic {

ListAtomicCell::ListAtomicCell() :
  m_name(KDFont::SmallFont, I18n::Message::Default, 0,0, KDColorBlack, Palette::GrayMiddle)
{
}

void ListAtomicCell::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorWhite);
  ctx->fillRect(m_atomRect(), Palette::GrayMiddle);

  KDPoint symbolPoint(m_atomRect().x() + m_atomRect().width() / 2 - KDFont::LargeFont->stringSize(m_atom.symbol).width() / 2,
    m_atomRect().y() + m_atomRect().height() / 2 - KDFont::LargeFont->stringSize(m_atom.symbol).height() / 2);
  ctx->drawString(m_atom.symbol, symbolPoint, KDFont::LargeFont, KDColorBlack, Palette::GrayMiddle);

  char protons[4];
  Poincare::Integer(m_atom.num).serialize(protons, 4);
  KDPoint protonsPoint(m_atomRect().right() - KDFont::LargeFont->stringSize(protons).width() - k_padding,
    m_atomRect().top() + k_padding);
  ctx->drawString(protons, protonsPoint, KDFont::SmallFont, KDColorBlack, Palette::GrayMiddle);
}

View * ListAtomicCell::subviewAtIndex(int index) {
  assert(index == 0);
  return &m_name;
}

void ListAtomicCell::setAtom(AtomDef atom) {
  m_atom = atom;
  m_name.setMessage(atom.name);
}

KDRect ListAtomicCell::m_atomRect() const {
  return KDRect((bounds().left() + (bounds().width()- k_width) / 2), bounds().top() + k_margin, k_width, bounds().height() - 2*k_margin);
}

void ListAtomicCell::layoutSubviews(bool force) {
  KDRect nameRect(m_atomRect().bottomLeft().x() + k_padding, m_atomRect().bottomLeft().y() - KDFont::SmallFont->glyphSize().height(),
   m_atomRect().width() - k_padding, KDFont::SmallFont->glyphSize().height());
  m_name.setFrame(nameRect, force);
}

}
