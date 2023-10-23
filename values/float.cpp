#include "values.h"
#include "temps.h"
#include "../state.h"

float_value::float_value(float val) : value(FLOAT_T), _val(val) {}

float_value::float_value(const char *s) : value(FLOAT_T)
{
    this->_val = atof(s);
}

std::string float_value::to_string() const
{
    return std::to_string(this->_val);
}

gc_ptr<value> float_value::copy() const
{
    return new float_value(this->_val);
}

gc_ptr<value> float_value::convert(int type) const
{
    gc_ptr<value> val = nullptr;
    switch (type)
    {
    case FLOAT_T:
        val = this->copy();
        break;

    case INT_T:
        val = new int_value(this->_val);
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

VALUE_OP_TEMPLATE_C(float_value, *, float_value)
VALUE_OP_TEMPLATE_C(float_value, /, float_value)
VALUE_OP_TEMPLATE_C(float_value, +, float_value)
VALUE_OP_TEMPLATE_C(float_value, -, float_value)

VALUE_OP_TEMPLATE_C(float_value, >, bool_value)
VALUE_OP_TEMPLATE_C(float_value, <, bool_value)
VALUE_OP_TEMPLATE_C(float_value, >=, bool_value)
VALUE_OP_TEMPLATE_C(float_value, <=, bool_value)
VALUE_OP_TEMPLATE_C(float_value, ==, bool_value)
VALUE_OP_TEMPLATE_C(float_value, !=, bool_value)

VALUE_OP_TEMPLATE(float_value, =, float_value)