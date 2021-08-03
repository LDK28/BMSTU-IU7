#include "composite.h"
#include <stdarg.h>


Composite::Composite(std::shared_ptr<Object> first, ...)
{
    for (shared_ptr<Object>* ptr = &first; *ptr; ++ptr)
        vector.push_back(*ptr);
}

bool Composite::add(shared_ptr<Object> &obj)
{
    vector.push_back(obj);

    return true;
}

bool Composite::remove(const IteratorObject &it)
{
    vector.erase(it);

    return true;
}

void Composite::conversion(const Point &transfer, const ScaleCoef &scale, const Angle &angle)
{
    for (const auto &elem : vector)
        elem->conversion(transfer, scale, angle);
}


void Composite::accept(Visitor &visitor)
{
    for (const auto &elem : vector)
        elem->accept(visitor);
}
