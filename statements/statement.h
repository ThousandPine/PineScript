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
    const std::string _exec_msg;
    const int _end_lineno;

    virtual void init() const;
    virtual int run() const = 0;
    virtual void exit() const;

public:
    gc_ptr<statement> next = nullptr;

    statement(const std::string &exec_msg, const int end_lineno);
    virtual ~statement(){}
    virtual int exec() const final;
};