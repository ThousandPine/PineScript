#pragma once

#include "expression.h"

class not_expression : public expression
{
protected:
    const gc_ptr<expression> _expr;

public:
    not_expression(const gc_ptr<expression> &expr);
    virtual gc_ptr<const value> get_value() const override;
};
