#include "not.h"

not_expression::not_expression(const gc_ptr<expression> &expr) : _expr(expr) {}

gc_ptr<value> not_expression::get_value() const
{
    auto val = _expr->get_value();
    return val == nullptr ? nullptr : !(*val);
}