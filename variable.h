#pragma once

#include <string>

#include "gc_ptr.h"
#include "values/value.h"

class variable
{
private:
    gc_ptr<value> _val;

    variable(const std::string &id, const gc_ptr<value> &val, int type, bool is_ref);

public:
    static variable *create(const std::string &id, int type, bool is_ref, const gc_ptr<value> &val);

    const int type;
    const bool is_ref;
    const std::string id;

    virtual gc_ptr<value> get_value() const;
    virtual gc_ptr<value> get_ref() const;
};