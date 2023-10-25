#pragma once

#include <string.h>

#include "value.h"

class string_value : public value
{
protected:
    std::string _val{};

public:
    string_value(const std::string &val);
    string_value(const char *s);

    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;

    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator+(const value &val) const override;
    virtual gc_ptr<value> operator>(const value &val) const override;
    virtual gc_ptr<value> operator<(const value &val) const override;
    virtual gc_ptr<value> operator>=(const value &val) const override;
    virtual gc_ptr<value> operator<=(const value &val) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual void operator=(const value &val) override;
};