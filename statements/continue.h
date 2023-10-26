#pragma once

#include "statement.h"

class continue_statement : public statement
{
protected:
    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    continue_statement();
};