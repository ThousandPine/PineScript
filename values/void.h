#pragma once

#include "value.h"

class void_value : public value
{
public:
    void_value();

    using value::operator=;
};
