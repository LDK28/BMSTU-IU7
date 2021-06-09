#include <stdio.h>
#include "BaseVector.h"

BaseVector::BaseVector()
{
    num_elem = 0;
}

BaseVector::~BaseVector()
{
    num_elem = 0;
}

BaseVector::BaseVector(const BaseVector& base)
{
    num_elem = base.num_elem;
}

int BaseVector::get_size() const
{
    return num_elem;
}

bool BaseVector::is_empty() const
{
    return !num_elem;
}
