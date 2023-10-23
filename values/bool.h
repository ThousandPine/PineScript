#pragma once

#include "value.h"

class bool_value : public value
{
protected:
    bool _val;

public:
    bool_value(bool val);
    bool_value(const char *s);

    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;

    virtual gc_ptr<value> operator!() const override;
    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual gc_ptr<value> operator=(const value &val) override;
};
