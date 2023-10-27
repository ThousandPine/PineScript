#pragma once

#include "expression.h"

class index_expression : public expression
{
protected:
    const gc_ptr<expression> _expr1, _expr2;

public:
    index_expression(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2);
    virtual gc_ptr<const value> get_value() const override;
    virtual gc_ptr<value> get_ref() const override;
};