#pragma once

#include "expression.h"

class assign_expression : public expression
{
protected:
    const gc_ptr<expression> _expr1, _expr2;

public:
    assign_expression(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2);
    virtual gc_ptr<const value> get_value() const override;
    virtual gc_ptr<value> get_ref() const override;
};