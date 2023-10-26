#pragma once

#include "statement.h"
#include "../expressions/expression.h"

class condition : public statement
{
protected:
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    condition(const gc_ptr<expression> &expr, int end_lineno);
};