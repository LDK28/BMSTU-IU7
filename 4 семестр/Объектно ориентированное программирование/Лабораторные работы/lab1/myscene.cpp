#include "myscene.h"
#include "math.h"
#include<iostream>

rc_type draw_line_scene(myscene_t scene, const point& p1, const point& p2)
{
    double z1 = sqrt(2)/2 * get_point_z(p1);
    double z2 = sqrt(2)/2 * get_point_z(p2);
    scene.scene->addLine(get_point_x(p1) - z1, - get_point_y(p1)+z1,
                         get_point_x(p2) - z2, - get_point_y(p2) + z2);
    return OK;
}

void draw_point_scene(myscene_t scene, const point& p1)
{
    double z1 = sqrt(2)/2 * get_point_z(p1);
    scene.scene->addEllipse(get_point_x(p1) - z1, - get_point_y(p1)+z1,1,1);
}

void clear_scene(myscene_t scene)
{
    scene.scene->clear();
}


