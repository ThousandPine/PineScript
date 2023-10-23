#include "values.h"
#include "temps.h"
#include "../state.h"

int_value::int_value(int val) : value(INT_T), _val(val) {}

int_value::int_value(const char *s) : value(INT_T)
{
    this->_val = atoi(s);
}

std::string int_value::to_string() const
{
    return std::to_string(this->_val);
}

gc_ptr<value> int_value::copy() const
{
    return new int_value(this->_val);
}

gc_ptr<value> int_value::convert(int type) const
{
    gc_ptr<value> val = nullptr;
    switch (type)
    {
    case INT_T:
        val = this->copy();
        break;

    case FLOAT_T:
        val = new float_value(this->_val);
        break;

    case BOOL_T:
        val = new bool_value(this->_val);
        break;

    default:
        CONVERT_ERROR();
        break;
    }
    return val;
}

VALUE_OP_TEMPLATE_C(int_value, *, int_value)
VALUE_OP_TEMPLATE_C(int_value, /, int_value)
VALUE_OP_TEMPLATE_C(int_value, %, int_value)
VALUE_OP_TEMPLATE_C(int_value, +, int_value)
VALUE_OP_TEMPLATE_C(int_value, -, int_value)

VALUE_OP_TEMPLATE_C(int_value, >, bool_value)
VALUE_OP_TEMPLATE_C(int_value, <, bool_value)
VALUE_OP_TEMPLATE_C(int_value, >=, bool_value)
VALUE_OP_TEMPLATE_C(int_value, <=, bool_value)
VALUE_OP_TEMPLATE_C(int_value, ==, bool_value)
VALUE_OP_TEMPLATE_C(int_value, !=, bool_value)

VALUE_OP_TEMPLATE(int_value, =, int_value)