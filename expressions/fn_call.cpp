#include "fn_call.h"
#include "../symtable.h"
#include "../values/void.h"
#include "../state.h"

fncall_expression::fncall_expression(const std::string &id, const gc_ptr<expr_list> &args) : _id(id), _expr_list(args) {}

gc_ptr<const value> fncall_expression::get_value() const
{
    gc_ptr<const value> ret_val = nullptr;

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
    auto expr_node = _expr_list;

    for (; arg != nullptr && expr_node != nullptr; arg = arg->next, expr_node = expr_node->next)
    {
        /* 创建参数变量 */
        gc_ptr<variable> var = nullptr;

        if (arg->is_ref)
        {
            auto val = expr_node->expr->get_ref();
            var = variable::create_ref(arg->id, arg->type, val);
        }
        else
        {
            auto val = expr_node->expr->get_value();
            var = variable::create_new(arg->id, arg->type, val);
        }

        if (var == nullptr)
        {
            return nullptr;
        }
        if (symtable::instance().def_var(var) == false)
        {
            return nullptr;
        }
    }

    if (arg != nullptr && expr_node == nullptr)
    {
        state::error("too few arguments in function \"" + fn->id + "\" call");
        return nullptr;
    }
    if (arg == nullptr && expr_node != nullptr)
    {
        state::error("too many arguments in function \"" + fn->id + "\" call");
        return nullptr;
    }

    return fn;
}

gc_ptr<const value> fncall_expression::_fn_run(gc_ptr<function> fn) const
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