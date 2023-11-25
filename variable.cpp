#include "variable.h"
#include "state.h"

/**
 * @brief 创建变量
 *
 * @param id 变量名
 * @param type 变量类型，若是NULL_T则根据val的type来定义
 * @param val 初始值指针
 *
 * @return 返回创建的变量指针，失败时返回nullptr
 *
 * @warning 失败情况：val == nullptr
 */
gc_ptr<variable> variable::create_new(const std::string &id, int type, const gc_ptr<const value> &val)
{
    if (val == nullptr)
    {
        return nullptr;
    }

    if (type != NULL_T && val->type != type)
    {
        state::error("a variable \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
        return nullptr;
    }
    return new variable(id, val->copy());
}

/**
 * @brief 创建变量引用
 *
 * @param id 变量名
 * @param type 变量类型，若是NULL_T则根据val的type来定义
 * @param val 初始值指针
 *
 * @return 返回创建的变量指针，失败时返回nullptr
 *
 * @warning 失败情况：val == nullptr
 */
gc_ptr<variable> variable::create_ref(const std::string &id, int type, const gc_ptr<value> &val)
{
    if (val == nullptr)
    {
        return nullptr;
    }

    /* 引用 */
    if (type != NULL_T && val->type != type)
    {
        state::error("a reference \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
        return nullptr;
    }
    return new variable(id, val);
}

/* ============================================== */

variable::variable(const std::string &id, const gc_ptr<value> &val)
    : _val(val), id(id) {}

gc_ptr<value> variable::get_value() const
{
    if (this->_val == nullptr)
    {
        state::error("using uninitialized variables \"" + this->id + "\"");
        return nullptr;
    }

    return this->_val;
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
