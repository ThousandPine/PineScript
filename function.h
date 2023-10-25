#pragma once

#include <stack>
#include <string>

#include "./values/value.h"
#include "./statements/statement.h"
#include "./expressions/expression.h"

class args_def
{
public:
    const std::string id;
    const int type;
    const bool is_ref;
    gc_ptr<args_def> next = nullptr;

    args_def(const std::string &id, int type, bool is_ref);
};

class expr_list
{
public:
    const gc_ptr<expression> expr;
    gc_ptr<expr_list> next = nullptr;

    expr_list(const gc_ptr<expression> &expr);
};

class function
{
public:
    static gc_ptr<value> return_val;
    static std::stack<gc_ptr<function>> fncall_stack;

    const std::string id;
    const int type;
    const gc_ptr<args_def> args;
    const gc_ptr<statement> statements;

    function(const std::string &id, int type, const gc_ptr<args_def> &args, const gc_ptr<statement> &statements);
};
