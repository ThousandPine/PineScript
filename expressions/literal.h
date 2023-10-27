#pragma once

#include "expression.h"

class literal : public expression
{
private:
    const gc_ptr<value> _val;

public:
    literal(const gc_ptr<value> &val);

    virtual gc_ptr<const value> get_value() const override;
};