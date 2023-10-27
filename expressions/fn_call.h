#pragma once

#include "expression.h"
#include "../function.h"

class fncall_expression : public expression
{
private:
    const std::string _id;
    const gc_ptr<expr_list> _expr_list;

    gc_ptr<function> _fn_init() const;
    gc_ptr<const value> _fn_run(gc_ptr<function> fn) const;

public:
    fncall_expression(const std::string &id, const gc_ptr<expr_list> &args);
    virtual gc_ptr<const value> get_value() const override;
};