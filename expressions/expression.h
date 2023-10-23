#pragma once

#include <string>

#include "../gc_ptr.h"
#include "../values/value.h"

class expression
{
public:
    virtual gc_ptr<value> get_value() const = 0;
    virtual gc_ptr<value> get_ref() const;
};

class literal : public expression
{
private:
    const gc_ptr<value> _val;

public:
    literal(const gc_ptr<value> &val);

    virtual gc_ptr<value> get_value() const override;
};
