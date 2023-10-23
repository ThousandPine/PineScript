#include "values.h"
#include "../state.h"

void_value::void_value() : value(VOID_T) {}

void void_value::input()
{
    state::error("input cannot be performed on void type");
    return;
}
void void_value::output() const
{
    state::error("output cannot be performed on void type");
    return;
}

std::string void_value::to_string() const
{
    return "";
}
gc_ptr<value> void_value::copy() const
{
    state::error("Cannot copy 'void' value");
    return nullptr;
}