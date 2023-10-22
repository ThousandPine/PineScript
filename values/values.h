#pragma once

#include "value.h"

class void_value : public value
{
public:
    void_value();

    virtual std::string to_string() const override;
    virtual gc_ptr<value> copy() const override;
};

class int_value : public value
{
protected:
    int _val;

public:
    int_value(int val);
    int_value(const char *s);

    virtual std::string to_string() const override;
    virtual gc_ptr<value> copy() const override;

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
    virtual gc_ptr<value> operator=(const value &val) override;
};

class float_value : public value
{
protected:
    float _val;

public:
    float_value(float val);
    float_value(const char *s);

    virtual std::string to_string() const override;
    virtual gc_ptr<value> copy() const override;

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

class bool_value : public value
{
protected:
    bool _val;

public:
    bool_value(bool val);
    bool_value(const char *s);

    virtual std::string to_string() const override;
    virtual gc_ptr<value> copy() const override;

    virtual gc_ptr<value> operator!() const override;
    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual gc_ptr<value> operator=(const value &val) override;
};