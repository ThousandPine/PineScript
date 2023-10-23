#include "statements.h"

output_statement::output_statement(const gc_ptr<expr_list> &exprs, int end_lineno)
    : statement("input", end_lineno),
      _exprs(exprs) {}

int output_statement::run() const
{
    for (auto p = _exprs; p !=nullptr; p = p->next)
    {
        auto val = p->expr->get_value();
        if (val == nullptr)
        {
            return ERROR;
        }
        val->output();
    }
    return DONE;
}