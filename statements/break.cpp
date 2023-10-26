#include "break.h"

break_statement::break_statement() : statement("", -1) {}

void break_statement::init() const
{
    /* 不创建执行记录 */
    return;
}
void break_statement::exit() const
{
    return;
}
int break_statement::run() const
{
    return BREAK;
}