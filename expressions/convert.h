#pragma once

#include "expression.h"

class convert_expression : public expression
{
protected:
    const int _type;
    const gc_ptr<expression> _expr;

public:
    convert_expression(const gc_ptr<expression> &expr, int type);
    virtual gc_ptr<value> get_value() const override;
};