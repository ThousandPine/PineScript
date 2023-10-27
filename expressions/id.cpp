#include "id.h"
#include "../symtable.h"

id_expression::id_expression(const std::string &id) : _id(id) {}

gc_ptr<const value> id_expression::get_value() const
{
    return this->get_ref();
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