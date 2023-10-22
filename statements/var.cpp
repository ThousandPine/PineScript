#include "statements.h"
#include "../symtable.h"
#include "../expressions/expression.h"

vardef_statement::vardef_statement(const std::string &id, int type, const gc_ptr<expression> &expr, int end_lineno)
    : statement("define variable \"" + id + "\"", end_lineno),
      _id(id), _type(type), _expr(expr) {}

int vardef_statement::run() const
{
    auto var = variable::create(this->_id, this->_type, false, this->_expr == nullptr ? nullptr : this->_expr->get_value());

    if (var == nullptr)
    {
        return ERROR;
    }
    symtable::instance().def_var(var);
    return DONE;
}

/* ========================================== */

varref_statement::varref_statement(const std::string &id, int type, const std::string &ref_id, int end_lineno)
    : statement("define variable \"" + id + "\"", end_lineno),
      _id(id), _type(type), _ref_id(ref_id) {}

int varref_statement::run() const
{
    auto ref_var = symtable::instance().get_var(this->_ref_id);
    if (ref_var == nullptr)
    {
        return ERROR;
    }

    auto var = variable::create(this->_id, this->_type, true, ref_var->get_ref());

    if (var == nullptr)
    {
        return ERROR;
    }
    symtable::instance().def_var(var);
    return DONE;
}