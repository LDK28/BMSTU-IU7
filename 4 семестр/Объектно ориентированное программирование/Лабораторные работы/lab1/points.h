#ifndef POINTS_H
#define POINTS_H


struct point
{
    double x;
    double y;
    double z;
    int n;
};

typedef point* array_t;

double get_point_x(const point& a);
double get_point_y(const point& a);
double get_point_z(const point& a);
int get_point_n(const point& a);
void set_point_x(point& a, double x);
void set_point_y(point& a, double y);
void set_point_z(point& a, double z);
void set_point_n(point& a, int n);
void set_point(point& a, double x, double y, double z, int n);
double rotate_point(double xa, double xc, double sinp, double cosp, double pa, double pc);

#endif
