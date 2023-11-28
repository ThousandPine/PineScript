#include "index.h"
#include "../symtable.h"

index_expression::index_expression(const gc_ptr<expression> &expr1, const gc_ptr<expression> &expr2) : _expr1(expr1), _expr2(expr2) {}

gc_ptr<const value> index_expression::get_value() const
{
    return this->get_ref();
}

gc_ptr<value> index_expression::get_ref() const
{
    auto ref = _expr1->get_ref();
    if (ref == nullptr)
    {
        return nullptr;
    }
    auto val = _expr2->get_value();
    if (val == nullptr)
    {
        return nullptr;
    }

    return (*ref)[(*val)];
}