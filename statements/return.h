#pragma once

#include "statement.h"
#include "../expressions/expression.h"

class return_statement : public statement
{
private:
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    return_statement(const gc_ptr<expression> &expr, int end_lineno);
};