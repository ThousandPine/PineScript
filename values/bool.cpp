#include <iostream>
#include <string.h>

#include "values.h"
#include "temps.h"
#include "../state.h"

bool_value::bool_value(bool val) : value(BOOL_T), _val(val) {}

/*
 * NOTE: 这里不能使用string来替代char *
 * 否则编译器会优先将传入的char *匹配为bool的重载
 */
bool_value::bool_value(const char *s) : value(BOOL_T)
{
    _val = strcmp(s, "false");
}

bool bool_value::val() const
{
    return _val;
}

std::string bool_value::to_string() const
{
    return _val ? "true" : "false";
}

gc_ptr<value> bool_value::copy() const
{
    return new bool_value(_val);
}

gc_ptr<value> bool_value::convert(int type) const
{
    gc_ptr<value> val = nullptr;
    switch (type)
    {
    case BOOL_T:
        val = this->copy();
        break;

    case INT_T:
        val = new int_value(_val);
        break;

    case STRING_T:
        val = new string_value(this->to_string());
        break;

    default:
        CONVERT_ERROR();
        break;
    }
    return val;
}

gc_ptr<value> bool_value::operator!() const
{
    return new bool_value(!_val);
}

VALUE_IO_TEMPLATE(bool_value)

VALUE_OP_TEMPLATE_C(bool_value, ==, bool_value)
VALUE_OP_TEMPLATE_C(bool_value, !=, bool_value)

VALUE_ASSIGN_TEMPLATE(bool_value)
