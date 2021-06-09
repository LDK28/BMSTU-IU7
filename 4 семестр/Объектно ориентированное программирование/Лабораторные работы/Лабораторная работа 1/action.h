#ifndef ACTION_H
#define ACTION_H

#include "points.h"
#include "figure.h"

struct alpha_t
{
    double ax;
    double ay;
    double az;
};

struct data
{
    const char* filename;
    alpha_t rotation;
    struct
    {
        double k;
    } scale ;
    struct
    {
        double dx;
        double dz;
        double dy;
    } move;
};

point& get_point(figure& fig, int i);
double get_alphax(const alpha_t& d);
double get_alphay(const alpha_t& d);
double get_alphaz(const alpha_t& d);
double get_deltax(const data& d);
double get_deltay(const data& d);
double get_deltaz(const data& d);
alpha_t get_alpha(const data& d);
double get_k(const data& d);

#endif
