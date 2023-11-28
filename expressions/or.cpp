#include "or.h"
#include "../state.h"
#include "../symtable.h"
#include "../values/bool.h"

or_expression::or_expression(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {}

gc_ptr<const value> or_expression::get_value() const
{
    /* 分开计算两个表达式实现短路 */
    decltype(_expr1) exprs[]{_expr1, _expr2};

    for (int i = 0; i < 2; ++i)
    {
        auto val = exprs[i]->get_value();
        if (val == nullptr)
        {
            return nullptr;
        }
        if (val->type != BOOL_T)
        {
            state::error("the operator '||' must be of type '" + value::type_to_name(BOOL_T) + "', but the provided operand type is of type '" + val->type_name() + "'");
            return nullptr;
        }
        if (true == ((const bool_value *)val.ptr())->val())
        {
            return val;
        }
    }

    return new bool_value(false);
}