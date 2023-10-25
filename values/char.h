#pragma once

#include "value.h"

class char_value : public value
{
protected:
    char _val;

public:
    static std::pair<char, int> escape(const char *s);

    char_value(char val);
    char_value(const char *s);

    virtual void input() override;
    virtual void output() const override;
    virtual gc_ptr<value> copy() const override;
    virtual std::string to_string() const override;

    virtual gc_ptr<value> convert(int type) const override;
    virtual gc_ptr<value> operator>(const value &val) const override;
    virtual gc_ptr<value> operator<(const value &val) const override;
    virtual gc_ptr<value> operator>=(const value &val) const override;
    virtual gc_ptr<value> operator<=(const value &val) const override;
    virtual gc_ptr<value> operator==(const value &val) const override;
    virtual gc_ptr<value> operator!=(const value &val) const override;
    virtual void operator=(const value &val) override;
};