#pragma once

#include "value.h"

class float_value : public value
{
protected:
    float _val;

public:
    float_value(float val);
    float_value(const char *s);

    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;

    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator*(const value &val) const override;
    virtual gc_ptr<value> operator/(const value &val) const override;
    virtual gc_ptr<value> operator+(const value &val) const override;
    virtual gc_ptr<value> operator-(const value &val) const override;
    virtual gc_ptr<value> operator>(const value &val) const override;
    virtual gc_ptr<value> operator<(const value &val) const override;
    virtual gc_ptr<value> operator>=(const value &val) const override;
    virtual gc_ptr<value> operator<=(const value &val) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual gc_ptr<value> operator=(const value &val) override;
};
