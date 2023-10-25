#pragma once

#include <string>

#include "../gc_ptr.h"
#include "../values/value.h"

class expression
{
public:
    virtual ~expression(){}

    virtual gc_ptr<value> get_value() const = 0;
    virtual gc_ptr<value> get_ref() const;
};
