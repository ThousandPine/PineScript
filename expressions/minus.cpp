#include "minus.h"

minus_expression::minus_expression(const gc_ptr<expression> &expr) : _expr(expr) {}

gc_ptr<const value> minus_expression::get_value() const
{
    auto val = _expr->get_value();
    return val == nullptr ? nullptr : -(*val);
}