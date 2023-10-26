#include "continue.h"

continue_statement::continue_statement() : statement("", -1) {}

void continue_statement::init() const
{
    /* 不创建执行记录 */
    return;
}
void continue_statement::exit() const
{
    return;
}
int continue_statement::run() const
{
    return CONTINUE;
}