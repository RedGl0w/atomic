#include "atomic_cell.h"
#include <assert.h>

namespace Atomic {

AtomicCell::AtomicCell() :
  HighlightCell(),
  m_visible(true)
{
}

KDColor AtomicCell::colorForType(AtomType type) const {
  switch(type) {
      case AtomType::UNKNOWN :                {return KDColor::RGB24(0xeeeeee);}
      case AtomType::ALKALI_METAL :           {return KDColor::RGB24(0xffaa00);}
      case AtomType::ALKALI_EARTH_METAL :     {return KDColor::RGB24(0xf6f200);}
      case AtomType::LANTHANIDE :             {return KDColor::RGB24(0xffaa8b);}
      case AtomType::ACTINIDE :               {return KDColor::RGB24(0xdeaacd);}
      case AtomType::TRANSITION_METAL :       {return KDColor::RGB24(0xde999c);}
      case AtomType::POST_TRANSITION_METAL :  {return KDColor::RGB24(0x9cbaac);}
      case AtomType::METALLOID :              {return KDColor::RGB24(0x52ce8b);}
      case AtomType::HALOGEN :                {return KDColor::RGB24(0x00debd);}
      case AtomType::REACTIVE_NONMETAL :      {return KDColor::RGB24(0x00ee00);}
      case AtomType::NOBLE_GAS :              {return KDColor::RGB24(0x8baaff);}

      default:                                {assert(false); return KDColorBlack;}
    }
}


void AtomicCell::drawRect(KDContext * ctx, KDRect rect) const {
  if(m_visible) {
    KDColor color = colorForType(m_atom.type);
    ctx->fillRect(rect, color);
    ctx->strokeRect(bounds(), KDColorBlack);
    KDPoint textPosition(bounds().topLeft().x() + 2, bounds().topLeft().y() + 2);
    ctx->drawString(m_atom.symbol, textPosition, KDFont::SmallFont, KDColorBlack, color);
  } else {
    ctx->fillRect(rect, KDColorWhite);
  }
  if (isHighlighted()) {
    KDColor highlightColor = KDColor::RGB24(0x313431);
    KDRect rect1(bounds().topLeft().x() + 1, bounds().topLeft().y() + 1, bounds().width() - 2, bounds().height() - 2);
    KDRect rect2(bounds().topLeft().x() + 2, bounds().topLeft().y() + 2, bounds().width() - 3, bounds().height() - 3);
    ctx->strokeRect(rect1, highlightColor);
    ctx->strokeRect(rect2, highlightColor);
  }
}

int AtomicCell::numberOfSubviews() const {
  return 0;
}

View * AtomicCell::subviewAtIndex(int index) {
  return nullptr;
}

void AtomicCell::layoutSubviews(bool force) {
}

void AtomicCell::setVisible(bool visible) {
  if (m_visible != visible) {
    m_visible = visible;
    markRectAsDirty(bounds());
  }
}

void AtomicCell::setAtom(AtomDef atom) {
  m_atom = atom;
  markRectAsDirty(bounds());
}

void AtomicCell::reloadCell() {
  markRectAsDirty(bounds());
}

}
