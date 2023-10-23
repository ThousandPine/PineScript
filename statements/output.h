#pragma once

#include "statement.h"
#include "../function.h"

class output_statement : public statement
{
private:
    const gc_ptr<expr_list> _expr_list;

    virtual int run() const override;

public:
    output_statement(const gc_ptr<expr_list> &expr_list, int end_lineno);
};
