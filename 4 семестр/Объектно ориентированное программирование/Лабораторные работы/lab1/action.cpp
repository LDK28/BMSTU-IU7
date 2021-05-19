#include "action.h"
#include "figure.h"
#include <string.h>


point& get_point(figure& fig, int i)
{
    return fig.arr[i];
}

double get_alphax(const alpha_t& d)
{
    return d.ax;
}
double get_alphay(const alpha_t& d)
{
    return d.ay;
}
double get_alphaz(const alpha_t& d)
{
    return d.az;
}

alpha_t get_alpha(const data& d)
{
    return d.rotation;
}

double get_deltax(const data& d)
{
    return d.move.dx;
}
double get_deltay(const data& d)
{
    return d.move.dy;
}
double get_deltaz(const data& d)
{
    return d.move.dy;
}
double get_k(const data& d)
{
    return d.scale.k;
}
