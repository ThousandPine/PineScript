#pragma once

#include "statement.h"
#include "../function.h"

class blank_statement : public statement
{
protected:
    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    blank_statement();
};

class block_statement : public statement
{
protected:
    const gc_ptr<statement> _list;

    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    block_statement(const gc_ptr<statement> &list);
};

class expr_statement : public statement
{
protected:
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    expr_statement(const gc_ptr<expression> &expr, int end_lineno);
};

class fndef_statement : public statement
{
private:
    const gc_ptr<function> _fn;

    virtual void init() const override;
    virtual int run() const override;
    virtual void exit() const override;

public:
    fndef_statement(const gc_ptr<function> &fn);
};

class vardef_statement : public statement
{
private:
    const std::string _id;
    const int _type;
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    vardef_statement(const std::string &id, int type, const gc_ptr<expression> &expr, int end_lineno);
};

class varref_statement : public statement
{
private:
    const std::string _id, _ref_id;
    const int _type;

    virtual int run() const override;

public:
    varref_statement(const std::string &id, int type, const std::string &ref_id, int end_lineno);
};

class return_statement : public statement
{
private:
    const gc_ptr<expression> _expr;

    virtual int run() const override;

public:
    return_statement(const gc_ptr<expression> &expr, int end_lineno);
};
