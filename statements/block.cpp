#include "block.h"
#include "../state.h"
#include "../symtable.h"

block_statement::block_statement(const gc_ptr<statement> &list) : statement("", -1), _list(list) {}

void block_statement::init() const
{
    /* 不创建执行记录 */
    
    symtable::instance().enter_scope();
}

int block_statement::run() const
{
    int exec_state = DONE;
    auto stmt = this->_list;

    while (stmt != nullptr)
    {
        switch (exec_state = stmt->exec())
        {
        case DONE:
            stmt = stmt->next;
            break;

        case RETURN:
            return RETURN;

        case ERROR:
            return ERROR;
        default:
            state::error("unknown execution status " + std::to_string(exec_state));
            return ERROR;
        }
    }

    return exec_state;
}

void block_statement::exit() const
{
    symtable::instance().enter_scope();
}
