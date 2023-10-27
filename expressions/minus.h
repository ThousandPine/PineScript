#pragma once

#include "expression.h"

class minus_expression : public expression
{
protected:
    const gc_ptr<expression> _expr;

public:
    minus_expression(const gc_ptr<expression> &expr);
    virtual gc_ptr<const value> get_value() const override;
};