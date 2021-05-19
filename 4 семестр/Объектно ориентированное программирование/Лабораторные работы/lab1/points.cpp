#include"points.h"

double get_point_x(const point&  a)
{
    return a.x;
}

double get_point_y(const point&  a)
{
    return a.y;
}

double get_point_z(const point&  a)
{
    return a.z;
}

int get_point_n(const point&  a)
{
    return a.n;
}

void set_point_x(point& a, double x)
{
    a.x = x;
}
void set_point_y(point& a, double y)
{
    a.y = y;
}
void set_point_z(point& a, double z)
{
    a.z = z;
}
void set_point_n(point& a, int n)
{
    a.n = n;
}

void set_point(point& a, double x, double y, double z, int n)
{
    a.n = n;
    a.x = x;
    a.y = y;
    a.z = z;
}

double rotate_point(double xa, double xc, double sinp, double cosp, double pa, double pc)
{
    return xc + (xa- xc) * cosp + (pa - pc) * sinp;
}


