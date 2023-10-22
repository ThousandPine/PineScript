#include "expressions.h"
#include "../symtable.h"

#define EXPR_TEMPLATE(class, op)                                                                                      \
    class ::class(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {} \
                                                                                                                      \
    gc_ptr<value> class ::get_value() const                                                                           \
    {                                                                                                                 \
        auto val1 = _expr1->get_value();                                                                              \
        auto val2 = _expr2->get_value();                                                                              \
        if (val1 == nullptr || val2 == nullptr)                                                                       \
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

/* ====================================== */

id_expression::id_expression(const std::string &id) : _id(id) {}

gc_ptr<value> id_expression::get_value() const
{
    auto var = symtable::instance().get_var(this->_id);

    if (var == nullptr)
    {
        return nullptr;
    }
    return var->get_value();
}

gc_ptr<value> id_expression::get_ref() const
{
    auto var = symtable::instance().get_var(this->_id);

    if (var == nullptr)
    {
        return nullptr;
    }
    return var->get_ref();
}

/* ====================================== */

assign_expression::assign_expression(const std::string &id, const gc_ptr<expression> &expr) : _id(id), _expr(expr) {}

gc_ptr<value> assign_expression::get_value() const
{
    auto var = symtable::instance().get_var(this->_id);
    if (var == nullptr)
    {
        return nullptr;
    }

    auto val = _expr->get_value();
    if (val == nullptr)
    {
        return nullptr;
    }

    return var->assign(_expr->get_value()) ? var->get_value() : nullptr;
}

/* ====================================== */

not_expression::not_expression(const gc_ptr<expression> &expr) : _expr(expr) {}

gc_ptr<value> not_expression::get_value() const
{
    auto val = _expr->get_value();
    return val == nullptr ? nullptr : !(*val);
}

/* ====================================== */

convert_expression::convert_expression(const gc_ptr<expression> &expr, int type) : _expr(expr), _type(type) {}

gc_ptr<value> convert_expression::get_value() const
{
    auto val = _expr->get_value();
    return val == nullptr ? nullptr : val->convert(this->_type);
}