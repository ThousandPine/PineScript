#pragma once

#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "function.h"
#include "gc_ptr.h"
#include "variable.h"

class symtable
{
private:
    static symtable _global;
    static std::stack<symtable> _local;

    const bool _is_global = false;
    std::unordered_map<std::string, gc_ptr<function>> _fn_tab{};
    std::unordered_map<std::string, std::stack<gc_ptr<variable>>> _var_tab{};
    std::stack<std::unordered_set<std::string>> _id_record{};

    void undef_var(const std::string &id);

public:
    static symtable &instance();

    symtable(bool is_global = false);
    ~symtable();

    void enter_scope();
    void exit_scope();

    void enter_local();
    void exit_local();

    bool def_fn(const gc_ptr<function> &fn);
    gc_ptr<function> get_fn(const std::string &id);

    bool def_var(const gc_ptr<variable> &var);
    gc_ptr<variable> get_var(const std::string &id);
};
