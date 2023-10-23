#include "assign.h"
#include "../symtable.h"

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