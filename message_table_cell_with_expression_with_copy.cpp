#include "message_table_cell_with_expression_with_copy.h"

void MessageTableCellWithExpressionWithCopy::setLayoutWithCopy(Poincare::Layout layout) {
  setLayout(layout);
  m_layout = layout;
}

Poincare::Layout MessageTableCellWithExpressionWithCopy::layout() const {
  return m_layout;
}
