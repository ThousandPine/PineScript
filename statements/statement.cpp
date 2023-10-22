#include "statement.h"
#include "../state.h"

statement::statement(const std::string &exec_msg, const int end_lineno) : _exec_msg(exec_msg), _end_lineno(end_lineno) {}

void statement::init() const
{
    state::push(this->_exec_msg, this->_end_lineno);
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