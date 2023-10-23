#include "output.h"

output_statement::output_statement(const gc_ptr<expr_list> &expr_list, int end_lineno)
    : statement("input", end_lineno),
      _expr_list(expr_list) {}

int output_statement::run() const
{
    for (auto p = _expr_list; p !=nullptr; p = p->next)
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