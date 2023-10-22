#pragma once

#include <string>

#include "../gc_ptr.h"

enum exec_state
{
    DONE,
    RETURN,
    BREAK,
    CONTINUE,
    ERROR
};

class statement
{
protected:
    const int _end_lineno;
    const std::string _exec_msg;

    virtual void init() const;
    virtual int run() const = 0;
    virtual void exit() const;

public:
    gc_ptr<statement> next = nullptr;

    statement(const std::string &exec_msg, const int end_lineno);
    virtual int exec() const final;
};