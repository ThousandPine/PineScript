#include "convert.h"

convert_expression::convert_expression(const gc_ptr<expression> &expr, int type) : _expr(expr), _type(type) {}

gc_ptr<const value> convert_expression::get_value() const
{
    auto val = _expr->get_value();
    return val == nullptr ? nullptr : val->convert(_type);
}