#include "if.h"
#include "../state.h"
#include "../symtable.h"

if_statement::if_statement(const gc_ptr<statement> &condition, const gc_ptr<statement> &if_run, const gc_ptr<statement> &else_run)
    : statement("", -1),
      _condition(condition), _if_run(if_run), _else_run(else_run) {}

void if_statement::init() const
{
    /* 不创建执行记录 */

    symtable::instance().enter_scope();
}

int if_statement::run() const
{
    int exec_state = _condition->exec();

    switch (exec_state)
    {
    case MATCH:
        return _if_run->exec();

    case MISMATCH:
        return _else_run == nullptr ? DONE : _else_run->exec();

    case ERROR:
        return ERROR;
    default:
        state::error("unknown execution status " + std::to_string(exec_state));
        return ERROR;
    }
}

void if_statement::exit() const
{
    symtable::instance().exit_scope();
}
