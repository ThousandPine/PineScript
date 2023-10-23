#pragma once

#include "expression.h"

class id_expression : public expression
{
protected:
    const std::string _id;

public:
    id_expression(const std::string &id);
    virtual gc_ptr<value> get_value() const override;
    virtual gc_ptr<value> get_ref() const override;
};