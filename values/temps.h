#pragma once

#define CONVERT_ERROR() state::error((std::string) "cannot convert '" + this->type_name() + "' to '" + value::type_to_name(type) + "'")

#define VALUE_IO_TEMPLATE(value_type)   \
    void value_type::input()            \
    {                                   \
        std::cin >> this->_val;         \
    }                                   \
    void value_type::output() const     \
    {                                   \
        std::cout << this->to_string(); \
    }

#define VALUE_OP_TEMPLATE_C(value_type, op, return_type)                                                                    \
    gc_ptr<value> value_type::operator op(const value & val) const                                                          \
    {                                                                                                                       \
        if (val.type != this->type)                                                                                         \
        {                                                                                                                   \
            state::error("type '" +                                                                                         \
                         this->type_name() + "' does not support '" + #op + "' operations with '" + val.type_name() + "'"); \
            return nullptr;                                                                                                 \
        }                                                                                                                   \
        return new return_type(this->_val op((const value_type *)&val)->_val);                                              \
    }

#define VALUE_ASSIGN_TEMPLATE(value_type)                                                                         \
    bool value_type::operator=(const value &val)                                                                  \
    {                                                                                                             \
        if (val.type != this->type)                                                                               \
        {                                                                                                         \
            state::error("type '" +                                                                               \
                         this->type_name() + "' does not support '=' operations with '" + val.type_name() + "'"); \
            return false;                                                                                         \
        }                                                                                                         \
        this->_val = ((const value_type *)&val)->_val;                                                            \
        return true;                                                                                              \
    }
