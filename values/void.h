#pragma once

#include "value.h"

class void_value : public value
{
public:
    void_value();

    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;
};
