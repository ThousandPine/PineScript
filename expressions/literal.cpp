#include "literal.h"

literal::literal(const gc_ptr<value> &val) : _val(val) {}

gc_ptr<const value> literal::get_value() const
{
    return _val;
}
