#include <iostream>

#include "array.h"
#include "int.h"
#include "../state.h"

array_value::array_value(const value &val, int size) : value(ARRAY_T)
{
    while (size-- > 0)
    {
        _vals.emplace_back(val.copy());
    }
}

array_value::array_value(const array_value &val) : value(ARRAY_T)
{
    for (auto &val : val._vals)
    {
        _vals.emplace_back(val->copy());
    }
}

std::string array_value::to_string() const
{
    std::string s{'['};

    if (_vals.size())
    {
        s += _vals[0]->to_string();
    }
    for (size_t i = 1; i < _vals.size(); ++i)
    {
        s += ", ";
        s += _vals[i]->to_string();
    }

    return s += ']';
}

void array_value::output() const
{
    std::cout << this->to_string();
}

gc_ptr<value> array_value::copy() const
{
    return new array_value(*this);
}

gc_ptr<value> array_value::operator[](const value &val) const
{
    if (val.type != INT_T)
    {
        state::error("the index of operator '[]' must be of type '" + value::type_to_name(INT_T) + "', but the provided operand type is of type '" + val.type_name() + "'");
        return nullptr;
    }

    size_t index = ((const int_value *)&val)->val();
    if (index >= _vals.size())
    {
        state::error("index " + std::to_string(index) + " of operator '[]' is out of bounds");
        return nullptr;
    }

    return _vals[index];
}