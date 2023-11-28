#include "while.h"
#include "../state.h"
#include "../symtable.h"

while_statement::while_statement(const gc_ptr<statement> &condition, const gc_ptr<statement> &loop_run)
    : statement("", -1),
      _condition(condition), _loop_run(loop_run) {}

void while_statement::init() const
{
    /* 不创建执行记录 */

    symtable::instance().enter_scope();
}

int while_statement::run() const
{
    while (true)
    {
        /* 条件判断 */
        int exec_state = _condition->exec();
        switch (exec_state)
        {
        case MATCH:
            break;

        case MISMATCH:
            return DONE;
        case ERROR:
            return ERROR;
        default:
            state::error("unknown execution status " + std::to_string(exec_state));
            return ERROR;
        }

        /* 执行循环体 */
        exec_state = _loop_run->exec();
        switch (exec_state)
        {
        case DONE:
        case CONTINUE:
            break;

        case BREAK:
            return DONE;
        case ERROR:
            return ERROR;
        default:
            state::error("unknown execution status " + std::to_string(exec_state));
            return ERROR;
        }
    }
}

void while_statement::exit() const
{
    symtable::instance().exit_scope();
}
