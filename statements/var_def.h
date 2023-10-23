#pragma once

#include "statement.h"
#include "../expressions/expression.h"

class vardef_statement : public statement
{
private:
    const std::string _id;
    const int _type;
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    vardef_statement(const std::string &id, int type, const gc_ptr<expression> &expr, int end_lineno);
};

class varref_statement : public statement
{
private:
    const std::string _id, _ref_id;
    const int _type;

    virtual int run() const override;

public:
    varref_statement(const std::string &id, int type, const std::string &ref_id, int end_lineno);
};