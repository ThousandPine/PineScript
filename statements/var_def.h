#pragma once

#include "statement.h"
#include "../expressions/expression.h"

class vardef_statement : public statement
{
private:
    const std::string _id;
    const bool _is_ref;
    const int _type;
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    vardef_statement(const std::string &id, bool is_ref, int type, const gc_ptr<expression> &expr, int end_lineno);
};