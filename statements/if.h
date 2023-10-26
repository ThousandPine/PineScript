#pragma once

#include "statement.h"

class if_statement : public statement
{
protected:
    gc_ptr<statement> _condition, _if_run, _else_run;

    virtual void init() const;
    virtual int run() const;
    virtual void exit() const;

public:
    
    if_statement(const gc_ptr<statement> &condition, const gc_ptr<statement> &if_run, const gc_ptr<statement> &else_run);
};