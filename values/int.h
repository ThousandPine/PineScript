#pragma once

#include "value.h"

class int_value : public value
{
protected:
    int _val;

public:
    int_value(int val);
    int_value(const char *s);

    int val() const;
    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;

    virtual gc_ptr<value> operator-() const override;
    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator*(const value &val) const override;
    virtual gc_ptr<value> operator/(const value &val) const override;
    virtual gc_ptr<value> operator%(const value &val) const override;
    virtual gc_ptr<value> operator+(const value &val) const override;
    virtual gc_ptr<value> operator-(const value &val) const override;
    virtual gc_ptr<value> operator>(const value &val) const override;
    virtual gc_ptr<value> operator<(const value &val) const override;
    virtual gc_ptr<value> operator>=(const value &val) const override;
    virtual gc_ptr<value> operator<=(const value &val) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual bool operator=(const value &val) override;
};