#include <iostream>

#include "values.h"
#include "temps.h"
#include "../state.h"

string_value::string_value(const std::string &val) : value(STRING_T), _val(val) {}

string_value::string_value(const char *s) : value(STRING_T)
{
    for (++s; *s != '\"';)
    {
        if (*s != '\\')
        {
            this->_val.push_back(*s++);
            continue;
        }

        auto c = char_value::escape(s);
        if (c.second == -1)
        {
            ++s;
            continue;;
        }
        this->_val.push_back(c.first);
        s += c.second;
    }
}

std::string string_value::to_string() const
{
    return this->_val;
}

gc_ptr<value> string_value::copy() const
{
    return new string_value(this->_val);
}

gc_ptr<value> string_value::convert(int type) const
{
    gc_ptr<value> val = nullptr;
    switch (type)
    {
    case STRING_T:
        val = this->copy();
        break;

    default:
        CONVERT_ERROR();
        break;
    }
    return val;
}

VALUE_IO_TEMPLATE(string_value)

VALUE_OP_TEMPLATE_C(string_value, +, string_value)
VALUE_OP_TEMPLATE_C(string_value, >, bool_value)
VALUE_OP_TEMPLATE_C(string_value, <, bool_value)
VALUE_OP_TEMPLATE_C(string_value, >=, bool_value)
VALUE_OP_TEMPLATE_C(string_value, <=, bool_value)
VALUE_OP_TEMPLATE_C(string_value, ==, bool_value)
VALUE_OP_TEMPLATE_C(string_value, !=, bool_value)

VALUE_ASSIGN_TEMPLATE(string_value)
