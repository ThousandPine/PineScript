#include "symtable.h"
#include "state.h"
#include "expressions/expressions.h"

symtable &symtable::instance()
{
    static symtable _instance;
    return _instance;
}

symtable::symtable()
{
    this->enter_scope();
}

symtable::~symtable()
{
    this->exit_scope();
}

void symtable::enter_scope()
{
    _id_record.push({});
}

void symtable::exit_scope()
{
    for (auto &id : _id_record.top())
    {
        undef_var(id);
    }
    _id_record.pop();
}

gc_ptr<function> symtable::get_fn(const std::string &id)
{
    auto it = _fn_tab.find(id);
    if (it == _fn_tab.end())
    {
        state::error("function \"" + id + "\" is not defined");
        return nullptr;
    }
    return it->second;
}

bool symtable::def_fn(const gc_ptr<function> &fn)
{
    if (fn == nullptr)
    {
        state::error("function definition is null");
        return false;
    }

    if (_fn_tab.find(fn->id) == _fn_tab.end())
    {
        _fn_tab.emplace(fn->id, fn);
        return true;
    }

    state::error("function \"" + fn->id + "\" has been defined.");
    return false;
}

bool symtable::def_var(const gc_ptr<variable> &var)
{
    if (var == nullptr)
    {
        state::error("variable definition is null");
        return false;
    }

    /* Shadowing 同作用域变量重复时进行重定义 */
    if (false == _id_record.top().emplace(var->id).second)
    {
        undef_var(var->id);
    }

    _var_tab[var->id].emplace(var);
    return true;
}

gc_ptr<variable> symtable::get_var(const std::string &id)
{
    auto &st = _var_tab[id];
    if (st.empty())
    {
        state::error("variable \"" + id + "\" is not defined");
        return nullptr;
    }
    return st.top();
}

void symtable::undef_var(const std::string &id)
{
    _var_tab[id].pop();
}