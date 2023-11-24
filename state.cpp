#include <iostream>

#include "state.h"

std::vector<std::string> state::_exec_stack;

void state::error(const std::string &s)
{
    std::cout << "\n<error> " << s << std::endl;
    print_stack();
}

void state::debug(const std::string &s)
{
    std::cout << "<debug> " << s << std::endl;
}

void state::print_stack()
{
    for (int i = _exec_stack.size() - 1; i >= 0; --i)
    {
        std::cout << "<stack> " << _exec_stack[i] << '\n';
    }
}

void state::push(const std::string &s)
{
    _exec_stack.emplace_back(s);
}

void state::pop()
{
    if (_exec_stack.size())
    {
        _exec_stack.pop_back();
    }
}