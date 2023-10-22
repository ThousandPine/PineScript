#include "statements.h"

expr_statement::expr_statement(const gc_ptr<expression> &expr, int end_lineno) : statement("expression", end_lineno) , _expr(expr) {}

int expr_statement::run() const
{
    return _expr->get_value() == nullptr ? ERROR : DONE;
}
