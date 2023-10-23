#include "blank.h"

blank_statement::blank_statement() : statement("", -1) {}

void blank_statement::init() const
{
    /* 不创建执行记录 */
    return;
}
void blank_statement::exit() const
{
    return;
}
int blank_statement::run() const
{
    return DONE;
}