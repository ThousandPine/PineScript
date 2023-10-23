#include "expressions.h"
#include "../statements/statement.h"
#include "../symtable.h"
#include "../values/values.h"
#include "../state.h"

fncall_expression::fncall_expression(const std::string &id, const gc_ptr<expr_list> &args) : _id(id), _exprs(args) {}

gc_ptr<value> fncall_expression::get_value() const
{
    gc_ptr<value> ret_val = nullptr;

    symtable::instance().enter_scope();

    auto fn = _fn_init();

    if (fn != nullptr)
    {
        state::push("call function \"" + this->_id + "\"");
        function::fncall_stack.push(fn);

        ret_val = _fn_run(fn);

        function::fncall_stack.pop();
        state::pop();
    }

    symtable::instance().exit_scope();
    return ret_val;
}

gc_ptr<function> fncall_expression::_fn_init() const
{
    /* 获取函数信息 */
    auto fn = symtable::instance().get_fn(_id);
    if (fn == nullptr)
    {
        return nullptr;
    }

    /* 传入参数 */
    auto arg = fn->args;
    auto e_list = _exprs;

    for (; arg != nullptr && e_list != nullptr; arg = arg->next, e_list = e_list->next)
    {
        /* 创建参数变量 */
        auto val = arg->is_ref ? e_list->expr->get_ref() : e_list->expr->get_value();
        if (val == nullptr)
        {
            return nullptr;
        }
        bool res = symtable::instance().def_var(variable::create(arg->id, arg->type, arg->is_ref, val));

        if (res == false)
        {
            return nullptr;
        }
    }

    if (arg != nullptr && e_list == nullptr)
    {
        state::error("too few arguments in function \"" + fn->id + "\" call");
        return nullptr;
    }
    if (arg == nullptr && e_list != nullptr)
    {
        state::error("too many arguments in function \"" + fn->id + "\" call");
        return nullptr;
    }

    return fn;
}

gc_ptr<value> fncall_expression::_fn_run(gc_ptr<function> fn) const
{
    /* 运行函数语句 */
    int exec_state = DONE;
    bool interrupt = false;
    auto stmt = fn->statements;

    while (!interrupt && stmt != nullptr)
    {
        switch (exec_state = stmt->exec())
        {
        case DONE:
            stmt = stmt->next;
            break;

        case RETURN:
            interrupt = true;
            break;

        case ERROR:
            return nullptr;

        default:
            state::error("unknown execution status " + std::to_string(exec_state));
            return nullptr;
        }
    }

    /* 处理返回值 */
    if (fn->type == VOID_T)
    {
        return new void_value();
    }

    /* 无返回值 */
    if (exec_state != RETURN)
    {
        state::error((std::string) "function \"" + fn->id + "\" does not return value");
        return nullptr;
    }

    return function::return_val;
}