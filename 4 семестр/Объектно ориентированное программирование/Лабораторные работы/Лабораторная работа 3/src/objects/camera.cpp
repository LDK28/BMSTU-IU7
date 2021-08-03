#include "camera.h"

void Camera::accept(Visitor &visitor)
{
}

void Camera::conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate)
{
    this->transfer(transfer);
    this->rotate(rotate);
}
