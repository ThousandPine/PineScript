#pragma once

#include <string>

#include "gc_ptr.h"
#include "values/value.h"

class variable
{
private:
    gc_ptr<value> _val;

    variable(const std::string &id, const gc_ptr<value> &val);

public:
    static gc_ptr<variable> create_new(const std::string &id, int type, const gc_ptr<const value> &val);
    static gc_ptr<variable> create_ref(const std::string &id, int type, const gc_ptr<value> &val);

    const std::string id;

    virtual ~variable() {}

    virtual gc_ptr<value> get_value() const;
    virtual gc_ptr<value> get_ref() const;
};