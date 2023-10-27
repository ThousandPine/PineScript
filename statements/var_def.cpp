#include "var_def.h"
#include "../symtable.h"

vardef_statement::vardef_statement(const std::string &id, bool is_ref, int type, const gc_ptr<expression> &expr, int end_lineno)
    : statement("define variable \"" + id + "\"", end_lineno),
      _id(id), _is_ref(is_ref), _type(type), _expr(expr) {}

int vardef_statement::run() const
{
    gc_ptr<variable> var = nullptr;

    if (this->_is_ref)
    {
        auto val = this->_expr->get_ref();
        var = variable::create_ref(this->_id, this->_type, val);
    }
    else
    {
        auto val = this->_expr->get_value();
        var = variable::create_new(this->_id, this->_type, val);
    }

    if (var == nullptr)
    {
        return ERROR;
    }
    if (symtable::instance().def_var(var) == false)
    {
        return ERROR;
    }
    return DONE;
}