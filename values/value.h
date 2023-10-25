#pragma once

#include <string>
#include <unordered_map>

#include "../gc_ptr.h"

enum value_t
{
    VOID_T,
    INT_T,
    FLOAT_T,
    CHAR_T,
    STRING_T,
    BOOL_T,

    NULL_T
};

class value
{
private:
    static std::unordered_map<int, std::string> _name;

public:
    static gc_ptr<value> create(int type);
    static const std::string &type_to_name(int type);

    const int type;

    value(int type);

    virtual void input();
    virtual void output() const;
    virtual gc_ptr<value> copy() const;
    virtual std::string to_string() const;
    virtual const std::string &type_name() const;

    virtual gc_ptr<value> operator-() const;
    virtual gc_ptr<value> operator!() const;
    virtual gc_ptr<value> convert(int type) const;
    virtual gc_ptr<value> operator*(const value &val) const;
    virtual gc_ptr<value> operator/(const value &val) const;
    virtual gc_ptr<value> operator%(const value &val) const;
    virtual gc_ptr<value> operator+(const value &val) const;
    virtual gc_ptr<value> operator-(const value &val) const;
    virtual gc_ptr<value> operator>(const value &val) const;
    virtual gc_ptr<value> operator<(const value &val) const;
    virtual gc_ptr<value> operator>=(const value &val) const;
    virtual gc_ptr<value> operator<=(const value &val) const;
    virtual gc_ptr<value> operator==(const value &val) const;
    virtual gc_ptr<value> operator!=(const value &val) const;
    virtual void operator=(const value &val);
};
