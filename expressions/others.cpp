#include "others.h"

#define EXPR_TEMPLATE(class, op)                                                                                      \
    class ::class(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {} \
                                                                                                                      \
    gc_ptr<const value> class ::get_value() const                                                                     \
    {                                                                                                                 \
        auto val1 = _expr1->get_value();                                                                              \
        if (val1 == nullptr)                                                                                          \
        {                                                                                                             \
            return nullptr;                                                                                           \
        }                                                                                                             \
        auto val2 = _expr2->get_value();                                                                              \
        if (val2 == nullptr)                                                                                          \
        {                                                                                                             \
            return nullptr;                                                                                           \
        }                                                                                                             \
        return (*val1)op(*val2);                                                                                      \
    }

EXPR_TEMPLATE(mul_expression, *)
EXPR_TEMPLATE(div_expression, /)
EXPR_TEMPLATE(mod_expression, %)
EXPR_TEMPLATE(add_expression, +)
EXPR_TEMPLATE(sub_expression, -)
EXPR_TEMPLATE(ge_expression, >)
EXPR_TEMPLATE(le_expression, <)
EXPR_TEMPLATE(geq_expression, >=)
EXPR_TEMPLATE(leq_expression, <=)
EXPR_TEMPLATE(eq_expression, ==)
EXPR_TEMPLATE(neq_expression, !=)
