#include "statements.h"
#include "../state.h"
#include "../values/values.h"

return_statement::return_statement(const gc_ptr<expression> &expr, int end_lineno)
    : statement("return", end_lineno),
      _expr(expr) {}

int return_statement::run() const
{
    auto val = this->_expr == nullptr ? new void_value() : this->_expr->get_value();

    if (val == nullptr)
    {
        return ERROR;
    }

    auto fn = function::fncall_stack.top();

    if (fn->type != val->type)
    {
        state::error((std::string) "funtion \"" + fn->id + "\" type is '" + value::type_to_name(fn->type) + "' but return '" + val->type_name() + "'");
        return ERROR;
    }

    function::return_val = val;
    return RETURN;
}
