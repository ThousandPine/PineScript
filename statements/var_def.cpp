#include "var_def.h"
#include "../symtable.h"

vardef_statement::vardef_statement(const std::string &id, bool is_ref, int type, const gc_ptr<expression> &expr, int end_lineno)
    : statement("define variable \"" + id + "\"", end_lineno),
      _id(id), _is_ref(is_ref), _type(type), _expr(expr) {}

int vardef_statement::run() const
{
    gc_ptr<variable> var = _is_ref ? variable::create_ref(_id, _type, _expr->get_ref())
                                   : variable::create_new(_id, _type, _expr->get_value());

    return var != nullptr && symtable::instance().def_var(var) ? DONE : ERROR;
}