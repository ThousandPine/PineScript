#pragma once

#include <vector>
#include <string>

class state
{
private:
    static std::vector<std::string> _exec_stack;

public:
    static void error(const std::string &s);
    static void print_stack();
    static void push(const std::string &s);
    static void push(const std::string &s, const int lineno);
    static void pop();
    static void debug(const std::string &s);
};