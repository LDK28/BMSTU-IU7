#ifndef POINT_H
#define POINT_H

#include "../Mathobj/mathobjs.h"
#include "math.h"

class Point
{
public:
    Point() = default;
    Point(double x, double y, double z) noexcept;

    Point(const Point &) noexcept;

    void transfer(const Point &transfer);
    void scale(const Point &center, const ScaleCoef &scale);
    void rotate(const Point &center, const Angle &angle);

    double get_x() const {return x;};
    double get_y() const {return y;};
    double get_z() const {return z;};

private:
    void rotate_xy(double angle);
    void rotate_xz(double angle);
    void rotate_yz(double angle);

    double x, y, z;
};

#endif // POINT_H
