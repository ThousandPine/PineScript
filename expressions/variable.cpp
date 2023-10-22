#include "expression.h"
#include "../state.h"

variable *variable::create(const std::string &id, int type, bool is_ref, const gc_ptr<value> &val)
{
    /* 引用 */
    if (is_ref)
    {
        if (val == nullptr)
        {
            state::error("reference variable \"" + id + "\" requires an initializer");
            return nullptr;
        }
        if (type != VOID_T && val->type != type)
        {
            state::error("a reference \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
            return nullptr;
        }
        return new variable(id, val, val->type, true);
    }

    /* 非引用 */
    if (val == nullptr)
    {
        if (type == VOID_T)
        {
            state::error("untyped variable \"" + id + "\" requires an initializer");
            return nullptr;
        }
        return new variable(id, nullptr, type, false);
    }
    if (type != VOID_T && val->type != type)
    {
        state::error("a variable \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
        return nullptr;
    }
    return new variable(id, val->copy(), val->type, false);
}

variable::variable(const std::string &id, const gc_ptr<value> &val, int type, bool is_ref)
    : _val(val), id(id), type(type), is_ref(is_ref) {}

gc_ptr<value> variable::get_value() const
{
    if (this->_val == nullptr)
    {
        state::error("using uninitialized variables \"" + this->id + "\"");
        return nullptr;
    }

    return this->_val->copy();
}

gc_ptr<value> variable::get_ref() const
{
    if (this->_val == nullptr)
    {
        state::error("variable '" + this->id + "' cannot be referenced before it is initialized");
        return nullptr;
    }

    return this->_val;
}

bool variable::assign(const gc_ptr<value> &val)
{
    if (val == nullptr)
    {
        return false;
    }

    /* 赋值 */
    if (this->_val != nullptr)
    {
        if (this->_val->type != val->type)
        {
            state::error((std::string) "a value of type '" + val->type_name() + "' cannot be assigned to variable \"" + this->id + "\" of type '" + value::type_to_name(this->type) + "'");
            return false;
        }
        *(this->_val) = *val;
    }
    /* 初始化 */
    else
    {
        if (this->_val->type != val->type)
        {
            state::error("a variable \"" + this->id + "\" of type '" + value::type_to_name(this->type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
            return false;
        }
        this->_val = val;
    }

    return true;
}
