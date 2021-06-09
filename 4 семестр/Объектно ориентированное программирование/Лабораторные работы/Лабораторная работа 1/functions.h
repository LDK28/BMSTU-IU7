#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "io.h"
#include "mainwindow.h"
#include "points.h"

#define PI 3.14

rc_type download_model(figure& fig, const data& act);
rc_type move_fig(figure& fig, const data& act);
rc_type rotation_fig(figure& fig, const data& act);
rc_type scale_fig(figure& fig, const data& act);
rc_type draw_fig(figure& fig, myscene_t scene);
void move(point& a, double dx, double dy, double dz);
void scale(point& a, const point& m, double k);
void rotation(point& a, const point& c, double ax, double ay, double az);

void draw_model(figure& fig, myscene_t scene);
#endif
