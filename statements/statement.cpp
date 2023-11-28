#include "statement.h"
#include "../state.h"

statement::statement(const std::string &exec_msg, const int end_lineno)
    : _exec_msg(exec_msg + " (end on line " + std::to_string(end_lineno) + ")") {}

void statement::init() const
{
    state::push(_exec_msg);
    return;
}

void statement::exit() const
{
    state::pop();
    return;
}

int statement::exec() const
{
    init();
    int state = run();
    exit();

    return state;
}