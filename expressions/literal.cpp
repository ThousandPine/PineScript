#include "expression.h"

literal::literal(const gc_ptr<value> &val):_val(val){}

gc_ptr<value> literal::get_value() const
{
    return this->_val->copy();
}
