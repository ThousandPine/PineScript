#pragma once

#include "expression.h"

class convert_expression : public expression
{
protected:
    const gc_ptr<expression> _expr;
    const int _type;

public:
    convert_expression(const gc_ptr<expression> &expr, int type);
    virtual gc_ptr<const value> get_value() const override;
};