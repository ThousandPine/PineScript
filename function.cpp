#include "function.h"
#include "expressions/expressions.h"

/* ================================= */

args_def::args_def(const std::string &id, int type, bool is_ref) : id(id), type(type), is_ref(is_ref) {}

/* ================================= */

expr_list::expr_list(const gc_ptr<expression> &expr) : expr(expr) {}

/* ================================= */

gc_ptr<const value> function::return_val = nullptr;
std::stack<gc_ptr<function>> function::fncall_stack;

function::function(const std::string &id, int type, const gc_ptr<args_def> &args, const gc_ptr<statement> &statements)
    : id(id), type(type), args(args), statements(statements) {}
