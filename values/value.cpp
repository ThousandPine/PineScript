#include "value.h"
#include "values.h"
#include "temps.h"
#include "../state.h"

std::unordered_map<int, std::string> value::_name{{VOID_T, "void"},
                                                  {INT_T, "int"},
                                                  {FLOAT_T, "float"},
                                                  {CHAR_T, "char"},
                                                  {STRING_T, "string"},
                                                  {BOOL_T, "bool"}};

const std::string &value::type_to_name(int type)
{
    return _name[type];
}

gc_ptr<value> value::create(int type)
{
    switch (type)
    {
    case VOID_T:
        return new void_value();
        break;
    case INT_T:
        return new int_value(0);
        break;
    case FLOAT_T:
        return new float_value(0.0);
        break;
    case BOOL_T:
        return new bool_value(false);
        break;
    case CHAR_T:
        return new char_value('\0');
        break;
    case STRING_T:
        return new string_value((std::string)"");
        break;

    default:
        state::error("value::create unknow type number " + std::to_string(type));
        return nullptr;
        break;
    }
}

/* ================================================= */

value::value(int type) : type(type) {}

const std::string &value::type_name() const
{
    return value::type_to_name(this->type);
}

void value::input()
{
    state::error("input cannot be performed on '" + this->type_name() + "' type");
    return;
}
void value::output() const
{
    state::error("output cannot be performed on '" + this->type_name() + "' type");
    return;
}
std::string value::to_string() const
{
    state::error("type '" + this->type_name() + "' does not support to string");
    return "";
}
gc_ptr<value> value::copy() const
{
    state::error("Cannot copy '" + this->type_name() + "' value");
    return nullptr;
}

gc_ptr<value> value::convert(int type) const
{
    CONVERT_ERROR();
    return nullptr;
}

#define OP_TEMPLATE(op)                                                                                       \
    gc_ptr<value> value::operator op(const value & val) const                                                 \
    {                                                                                                         \
        state::error((std::string) "type '" +                                                                 \
                     this->type_name() + "' does not support " + #op + " operations with" + val.type_name()); \
        return nullptr;                                                                                       \
    }

OP_TEMPLATE(*)
OP_TEMPLATE(/)
OP_TEMPLATE(%)
OP_TEMPLATE(+)
OP_TEMPLATE(-)
OP_TEMPLATE(>)
OP_TEMPLATE(<)
OP_TEMPLATE(>=)
OP_TEMPLATE(<=)
OP_TEMPLATE(==)
OP_TEMPLATE(!=)

gc_ptr<value> value::operator!() const
{
    state::error((std::string) "type '" + this->type_name() + "' does not support '!' operations");
    return nullptr;
}
gc_ptr<value> value::operator-() const
{
    state::error((std::string) "type '" + this->type_name() + "' does not support '-(minus)' operations");
    return nullptr;
}
gc_ptr<value> value::operator=(const value &val)
{
    state::error((std::string) "type '" +
                 this->type_name() + "' does not support '=' operations with" + val.type_name());
    return nullptr;
}
