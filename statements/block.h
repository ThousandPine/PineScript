#pragma once

#include "statement.h"

class block_statement : public statement
{
protected:
    const gc_ptr<statement> _list;

    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    block_statement(const gc_ptr<statement> &list);
};