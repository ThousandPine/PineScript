#include "variable.h"
#include "state.h"

/**
 * @brief 创建变量
 * 
 * @param id 变量名
 * @param type 变量类型，若是NULL_T则根据val的type来定义
 * @param is_ref 是否为引用类型
 * @param val 初始值指针，若类型是NULL_T则根据type参数创建初始值
 * 
 * @return 返回创建的变量指针，失败时返回nullptr
 * 
 * @warning 失败情况：
 * 1.val == nullptr
 * 2.type和val的type都为NULL_T
 * 3.用NULL_T初始化引用类型
 */
variable *variable::create(const std::string &id, int type, bool is_ref, const gc_ptr<value> &val)
{
    /* TODO: */
    if (val == nullptr)
    {
        return nullptr;
    }

    /* 引用 */
    if (is_ref)
    {
        if (val->type == NULL_T)
        {
            state::error("reference variable \"" + id + "\" requires an initializer");
            return nullptr;
        }
        if (type != NULL_T && val->type != type)
        {
            state::error("a reference \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
            return nullptr;
        }
        return new variable(id, val, val->type, true);
    }

    /* 非引用 */
    if (val->type == NULL_T)
    {
        if (type == NULL_T)
        {
            state::error("untyped variable \"" + id + "\" requires an initializer");
            return nullptr;
        }
        
        auto init_val = value::create(type);
        if (init_val == nullptr)
        {
            return nullptr;
        }
        return new variable(id, value::create(type), type, false);
    }
    if (type != NULL_T && val->type != type)
    {
        state::error("a variable \"" + id + "\" of type '" + value::type_to_name(type) + "' cannot be initialized with a value of type '" + val->type_name() + "'");
        return nullptr;
    }
    return new variable(id, val, val->type, false);
}

/* ============================================== */

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
