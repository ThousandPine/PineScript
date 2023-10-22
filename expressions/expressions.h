#pragma once

#include <queue>
#include <string>

#include "expression.h"
#include "../function.h"
#include "../gc_ptr.h"

/* ====================================== */

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

/* ====================================== */

class id_expression : public expression
{
protected:
    const std::string _id;

public:
    id_expression(const std::string &id);
    virtual gc_ptr<value> get_value() const override;
    virtual gc_ptr<value> get_ref() const override;
};

class fncall_expression : public expression
{
private:
    const std::string _id;
    const gc_ptr<expr_list> _exprs;

    gc_ptr<function> _fn_init() const;
    gc_ptr<value> _fn_run(gc_ptr<function> fn) const;

public:
    fncall_expression(const std::string &id, const gc_ptr<expr_list> &args);
    virtual gc_ptr<value> get_value() const override;
};

class not_expression : public expression
{
protected:
    const gc_ptr<expression> _expr;

public:
    not_expression(const gc_ptr<expression> &expr);
    virtual gc_ptr<value> get_value() const override;
};

class convert_expression : public expression
{
protected:
    const int _type;
    const gc_ptr<expression> _expr;

public:
    convert_expression(const gc_ptr<expression> &expr, int type);
    virtual gc_ptr<value> get_value() const override;
};

class assign_expression : public expression
{
protected:
    const std::string _id;
    const gc_ptr<expression> _expr;

public:
    assign_expression(const std::string &id, const gc_ptr<expression> &expr);
    virtual gc_ptr<value> get_value() const override;
};
