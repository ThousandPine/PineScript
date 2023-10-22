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

class variable : public expression
{
private:
    gc_ptr<value> _val;

    variable(const std::string &id, const gc_ptr<value> &val, int type, bool is_ref);

public:
    static variable *create(const std::string &id, int type, bool is_ref, const gc_ptr<value> &val);

    const int type;
    const bool is_ref;
    const std::string id;

    virtual gc_ptr<value> get_value() const override;
    virtual gc_ptr<value> get_ref() const override;
    virtual bool assign(const gc_ptr<value> &val);
};