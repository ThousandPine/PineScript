#pragma once

#define CONVERT_ERROR() state::error((std::string) "cannot convert '" + this->type_name() + "' to '" + value::type_to_name(type) + "'")

#define VALUE_OP_TEMPLATE_BODY(value_type, op, return_type)                                                                 \
    {                                                                                                                       \
        if (val.type != this->type)                                                                                         \
        {                                                                                                                   \
            state::error((std::string) "type '" +                                                                           \
                         this->type_name() + "' does not support '" + #op + "' operations with '" + val.type_name() + "'"); \
            return nullptr;                                                                                                 \
        }                                                                                                                   \
        return new return_type(this->_val op((const value_type *)&val)->_val);                                              \
    }

#define VALUE_OP_TEMPLATE_C(value_type, op, return_type)           \
    gc_ptr<value> value_type::operator op(const value & val) const \
    {                                                              \
        VALUE_OP_TEMPLATE_BODY(value_type, op, return_type)        \
    }

#define VALUE_OP_TEMPLATE(value_type, op, return_type)       \
    gc_ptr<value> value_type::operator op(const value & val) \
    {                                                        \
        VALUE_OP_TEMPLATE_BODY(value_type, op, return_type)  \
    }
