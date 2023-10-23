#pragma once

#include "expression.h"

class assign_expression : public expression
{
protected:
    const std::string _id;
    const gc_ptr<expression> _expr;

public:
    assign_expression(const std::string &id, const gc_ptr<expression> &expr);
    virtual gc_ptr<value> get_value() const override;
};