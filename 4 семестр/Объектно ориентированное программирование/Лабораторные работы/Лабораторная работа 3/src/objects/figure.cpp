#include "figure.h"

void Figure::conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate)
{
    this->transfer(transfer);
    this->rotate(rotate);
    this->scale(scale);
}

void Figure::transfer(const Point &transfer)
{
    data.transfer(transfer);
}


void Figure::rotate(const Angle &angle)
{
    data.rotate(angle);
}

void Figure::scale(const ScaleCoef &scale)
{
    data.scale(scale);
}

void Figure::accept(Visitor &visitor)
{
    visitor.visit(*this);
}
