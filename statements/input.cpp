#include "statements.h"

input_statement::input_statement(const gc_ptr<expr_list> &exprs, int end_lineno)
    : statement("input", end_lineno),
      _exprs(exprs) {}

int input_statement::run() const
{
    for (auto p = _exprs; p !=nullptr; p = p->next)
    {
        auto ref = p->expr->get_ref();
        if (ref == nullptr)
        {
            return ERROR;
        }
        ref->input();
    }
    return DONE;
}