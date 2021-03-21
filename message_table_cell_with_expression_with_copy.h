#ifndef ATOMIC_MESSAGE_TABLE_CELL_WITH_EXPRESSION_WITH_COPY_H
#define ATOMIC_MESSAGE_TABLE_CELL_WITH_EXPRESSION_WITH_COPY_H

#include <escher/message_table_cell_with_expression.h>

class MessageTableCellWithExpressionWithCopy : public MessageTableCellWithExpression {
public:
  void setLayoutWithCopy(Poincare::Layout layout);
  Poincare::Layout layout() const override;
private:
  Poincare::Layout m_layout;
};

#endif
