#pragma once

#include "expression.h"

#define EXPR_DEF_TEMPLATE(expr)                                                 \
    class expr : public expression                                              \
    {                                                                           \
    protected:                                                                  \
        const gc_ptr<expression> _expr1, _expr2;                                \
                                                                                \
    public:                                                                     \
        expr(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2); \
        virtual gc_ptr<value> get_value() const override;                       \
    };

EXPR_DEF_TEMPLATE(mul_expression)
EXPR_DEF_TEMPLATE(div_expression)
EXPR_DEF_TEMPLATE(mod_expression)
EXPR_DEF_TEMPLATE(add_expression)
EXPR_DEF_TEMPLATE(sub_expression)
EXPR_DEF_TEMPLATE(ge_expression)
EXPR_DEF_TEMPLATE(le_expression)
EXPR_DEF_TEMPLATE(geq_expression)
EXPR_DEF_TEMPLATE(leq_expression)
EXPR_DEF_TEMPLATE(eq_expression)
EXPR_DEF_TEMPLATE(neq_expression)