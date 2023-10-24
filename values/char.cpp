#include <iostream>

#include <string>
#include "values.h"
#include "temps.h"
#include "../state.h"

/**
 * 转义字符处理
 *
 * 返回处理后的转义字符和对应的字符数(加上'\'所以最小为2)
 * 遇到非法转义字符时返回字符数为-1
 */
std::pair<char, int> char_value::escape(const char *s)
{
    if (s[0] != '\\')
    {
        return {0, -1};
    }

    switch (s[1])
    {
    case 'n':
        return {'\n', 2};
    case 't':
        return {'\t', 2};
    case 'r':
        return {'\r', 2};
    case 'v':
        return {'\v', 2};
    case 'b':
        return {'\b', 2};
    case 'f':
        return {'\f', 2};
    case 'a':
        return {'\a', 2};
    case '\\':
        return {'\\', 2};
    case '\'':
        return {'\'', 2};
    case '\"':
        return {'\"', 2};
    case '?':
        return {'\?', 2};

    default:
        if (s[1] < '0' || s[1] > '7')
        {
            return {0, -1};
        }
        std::pair<char, int> result{s[1] - '0', 2};
        if (s[2] < '0' || s[2] > '7')
        {
            return result;
        }
        result.first = result.first * 8 + s[2] - '0';
        ++result.second;
        if (s[3] < '0' || s[3] > '7')
        {
            return result;
        }
        result.first = result.first * 8 + s[3] - '0';
        ++result.second;
        return result;
    }
    return {0, -1};
}

/* ================================================ */

char_value::char_value(char val) : value(CHAR_T), _val(val) {}

char_value::char_value(const char *s) : value(CHAR_T)
{
    this->_val = s[1] != '\\' ? s[1] : char_value::escape(s + 1).first;
}

std::string char_value::to_string() const
{
    return std::string(&this->_val, 1);
}

gc_ptr<value> char_value::copy() const
{
    return new char_value(this->_val);
}

gc_ptr<value> char_value::convert(int type) const
{
    gc_ptr<value> val = nullptr;
    switch (type)
    {
    case CHAR_T:
        val = this->copy();
        break;

    case INT_T:
        val = new int_value(this->_val);
        break;

    default:
        CONVERT_ERROR();
        break;
    }
    return val;
}

VALUE_IO_TEMPLATE(char_value)

VALUE_OP_TEMPLATE_C(char_value, >, bool_value)
VALUE_OP_TEMPLATE_C(char_value, <, bool_value)
VALUE_OP_TEMPLATE_C(char_value, >=, bool_value)
VALUE_OP_TEMPLATE_C(char_value, <=, bool_value)
VALUE_OP_TEMPLATE_C(char_value, ==, bool_value)
VALUE_OP_TEMPLATE_C(char_value, !=, bool_value)

VALUE_OP_TEMPLATE(char_value, =, char_value)
