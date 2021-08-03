#include "data.h"

void Data::transfer(const Point &transfer)
{
    center.transfer(transfer);
    for (auto &point : points)
        point.transfer(transfer);
}


void Data::rotate(const Angle &angle)
{
    for (auto &point : points)
        point.rotate(center, angle);
}

void Data::scale(const ScaleCoef &scale)
{
    for (auto &point : points)
        point.scale(center, scale);
}
