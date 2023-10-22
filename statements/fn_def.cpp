#include "statements.h"
#include "../symtable.h"

fndef_statement::fndef_statement(const gc_ptr<function> &fn) : statement("", -1) , _fn(fn) {}

void fndef_statement::init() const
{
    /* 不创建执行记录 */
    return;
}
void fndef_statement::exit() const
{
    return;
}

int fndef_statement::run() const
{
    if (symtable::instance().def_fn(_fn))
    {
        return DONE;
    }

    return ERROR;
}