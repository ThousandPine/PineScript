#pragma once

#include "value.h"

class null_value : public value
{
public:
    null_value();

    using value::operator=;
};
