#pragma once

#include "statement.h"
#include "../function.h"

class fndef_statement : public statement
{
private:
    const gc_ptr<function> _fn;

    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    fndef_statement(const gc_ptr<function> &fn);
};