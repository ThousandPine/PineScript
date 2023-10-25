#pragma once

#include <vector>

#include "value.h"

class array_value : public value
{
protected:
    std::vector<gc_ptr<value>> _vals{};

public:
    array_value(const value &val, int size);
    array_value(const array_value &val);

    virtual void output() const;
    virtual gc_ptr<value> copy() const;
    virtual std::string to_string() const;

    virtual gc_ptr<value> operator[](const value &val) const override;
    using value::operator=;
};