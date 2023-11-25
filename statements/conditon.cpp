#include "condition.h"
#include "../state.h"
#include "../values/bool.h"

condition::condition(const gc_ptr<expression> &expr, int end_lineno) : statement("condition judgment", end_lineno), _expr(expr) {}

int condition::run() const
{
    auto val = _expr->get_value();
    if (val == nullptr)
    {
        return ERROR;
    }
    if (val->type != BOOL_T)
    {
        state::error("the conditional statement only supports operands of type '" + value::type_to_name(BOOL_T) + "', but the provided operand is of type '" + val->type_name() + "'");
        return ERROR;
    }
    return ((const bool_value *)val.ptr())->val() ? MATCH : MISMATCH;
}
