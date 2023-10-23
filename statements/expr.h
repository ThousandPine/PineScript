#pragma once

#include "statement.h"
#include "../expressions/expression.h"

class expr_statement : public statement
{
protected:
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    expr_statement(const gc_ptr<expression> &expr, int end_lineno);
};