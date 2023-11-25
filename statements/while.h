#pragma once

#include "statement.h"

class while_statement : public statement
{
protected:
    gc_ptr<statement> _condition, _loop_run;

    virtual void init() const;
    virtual int run() const;
    virtual void exit() const;

public:
        while_statement(const gc_ptr<statement> &condition, const gc_ptr<statement> &loop_run);
};