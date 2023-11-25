#include "input.h"

input_statement::input_statement(const gc_ptr<expr_list> &expr_list, int end_lineno)
    : statement("input", end_lineno),
      _expr_list(expr_list) {}

int input_statement::run() const
{
    for (auto p = _expr_list; p != nullptr; p = p->next)
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