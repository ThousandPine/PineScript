#include "array_literal.h"
#include "../state.h"
#include "../values/int.h"
#include "../values/array.h"

array_literal::array_literal(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {}

gc_ptr<const value> array_literal::get_value() const
{
    auto val = _expr1->get_value();
    if (val == nullptr)
    {
        return nullptr;
    }

    auto size_val = _expr2->get_value();
    if (size_val == nullptr)
    {
        return nullptr;
    }
    if (size_val->type != INT_T)
    {
        state::error("the index of operator '[]' must be of type '" + value::type_to_name(INT_T) + "', but the provided operand type is of type '" + val->type_name() + "'");
        return nullptr;
    }

    int size = ((const int_value *)size_val.ptr())->val();
    if (size <= 0)
    {
        state::error("the size of an array must be greater than zero");
        return nullptr;
    }
    return new array_value(*val, size);
}