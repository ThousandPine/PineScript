#pragma once

#include "statement.h"

class break_statement : public statement
{
protected:
    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    break_statement();
};