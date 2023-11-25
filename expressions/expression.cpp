#include "expression.h"
#include "../state.h"

/**
 * 获取值引用
 *
 * NOTE: 默认定义为不可引用的rvalue
 *       lvalue请在子类重写该函数
 */
gc_ptr<value> expression::get_ref() const
{
    state::error("cannot reference rvalue");
    return nullptr;
}
