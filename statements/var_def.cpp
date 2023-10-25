#include "var_def.h"
#include "../symtable.h"

vardef_statement::vardef_statement(const std::string &id, bool is_ref, int type, const gc_ptr<expression> &expr, int end_lineno)
    : statement("define variable \"" + id + "\"", end_lineno),
      _id(id), _is_ref(is_ref), _type(type), _expr(expr) {}

int vardef_statement::run() const
{
    gc_ptr<value> val = nullptr;
    if (this->_expr == nullptr)
    {
        val = value::create(NULL_T);
    }
    else
    {
        val = this->_is_ref ? this->_expr->get_ref() : this->_expr->get_value();
    }
    
    auto var = variable::create(this->_id, this->_type, this->_is_ref, val);

    if (var == nullptr)
    {
        return ERROR;
    }
    symtable::instance().def_var(var);
    return DONE;
}