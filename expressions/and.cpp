#include "and.h"
#include "../state.h"
#include "../symtable.h"
#include "../values/bool.h"

and_expression::and_expression(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {}

gc_ptr<const value> and_expression::get_value() const
{
    /* 分开计算两个表达式实现短路 */
    decltype(this->_expr1) exprs[]{this->_expr1, this->_expr2};

    for (int i = 0; i < 2; ++i)
    {
        auto val = exprs[i]->get_value();
        if (val == nullptr)
        {
            return nullptr;
        }
        if (val->type != BOOL_T)
        {
        state::error("the '&&' operator only supports operands of type '" + value::type_to_name(BOOL_T) + "', but the provided operand is of type '" + val->type_name() + "'");
            return nullptr;
        }
        if (false == ((const bool_value *)val.ptr())->val())
        {
            return val;
        }
    }

    return new bool_value(true);
}