#include "values.h"
#include "../state.h"

void_value::void_value() : value(VOID_T) {}

std::string void_value::to_string() const
{
    return "";
}
gc_ptr<value> void_value::copy() const
{
    state::error("Cannot copy 'void' value");   
    return nullptr;
}