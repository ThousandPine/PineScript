#include "symtable.h"
#include "state.h"
#include "expressions/expressions.h"

symtable symtable::_global(true);
std::stack<symtable> symtable::_local{};

symtable &symtable::instance()
{
    return _local.empty() ? _global : _local.top();
}

symtable::symtable(bool is_global) : _is_global(is_global)
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
    if (_id_record.empty())
    {
        return;
    }

    for (auto &id : _id_record.top())
    {
        undef_var(id);
    }
    _id_record.pop();
}

void symtable::enter_local()
{
    _local.push({});
}

void symtable::exit_local()
{
    if (_local.size())
    {
        _local.pop();
    }
}

gc_ptr<function> symtable::get_fn(const std::string &id)
{
    // 只在全局符号表中寻找函数
    auto it = _global._fn_tab.find(id);
    if (it == _global._fn_tab.end())
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

    // 只在全局符号表中定义函数
    if (_global._fn_tab.find(fn->id) == _global._fn_tab.end())
    {
        _global._fn_tab.emplace(fn->id, fn);
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

    if (!_is_global)
    {
        return st.size() ? st.top() : _global.get_var(id);
    }

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