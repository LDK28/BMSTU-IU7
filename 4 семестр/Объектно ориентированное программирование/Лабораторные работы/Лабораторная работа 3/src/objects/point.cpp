#include "point.h"

Point::Point(double x, double y, double z) noexcept
    :x(x),
     y(y),
     z(z)
{

}

Point::Point(const Point &other) noexcept
    :x(other.x),
     y(other.y),
     z(other.z)
{

}

void Point::transfer(const Point &transfer)
{
    this->x += transfer.x;
    this->y += transfer.y;
    this->z += transfer.z;
}

static inline double toRads(double number)
{
    return number * M_PI / 180.0;
}

void Point::rotate_xy(double angle)
{
    double deg_angle = toRads(angle);

    double tmpx = x;
    double tmpy = y;

    x = tmpx * cos(deg_angle) - tmpy * sin(deg_angle);
    y = tmpx * sin(deg_angle) + tmpy * cos(deg_angle);
}

void Point::rotate_xz(double angle)
{
    double deg_angle = toRads(angle);

    double tmpx = x;
    double tmpz = z;

    x = tmpx * cos(deg_angle) - tmpz * sin(deg_angle);
    z = tmpx * sin(deg_angle) + tmpz * cos(deg_angle);
}


void Point::rotate_yz(double angle)
{
    double deg_angle = toRads(angle);

    double tmpy = y;
    double tmpz = z;

    y = tmpy * cos(deg_angle) - tmpz * sin(deg_angle);
    z = tmpy * sin(deg_angle) + tmpz * cos(deg_angle);
}

void Point::rotate(const Point &center, const Angle &angle)
{
    x -= center.x;
    y -= center.y;
    z -= center.z;

    rotate_xy(angle.get_xy());
    rotate_xz(angle.get_xz());
    rotate_yz(angle.get_yz());

    x += center.x;
    y += center.y;
    z += center.z;
}

void Point::scale(const Point &center, const ScaleCoef &scale)
{
    x = scale.get_kx() * x + center.x * (1.0 - scale.get_kx());
    y = scale.get_ky() * y + center.y * (1.0 - scale.get_ky());
    z = scale.get_kz() * z + center.z * (1.0 - scale.get_kz());
}
