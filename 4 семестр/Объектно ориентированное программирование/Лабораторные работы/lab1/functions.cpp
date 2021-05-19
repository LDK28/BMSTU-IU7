#include "io.h"
#include "mainwindow.h"
#include "functions.h"
#include "action.h"
#include "math.h"
#include "controller.h"
#include <iostream>

rc_type download_model(figure& fig, const data& act)
{
    stream_t stream;
    rc_type rc = open_file_read(stream, act.filename, FILE_OPEN_TYPE);
    if (rc)
        return rc;
    rc = read_from_file(fig, stream);
    fclose(stream);
    return rc;
}

void move(point& a, double dx, double dy, double dz)
{
    double x = get_point_x(a) + dx;
    double y = get_point_y(a) + dy;
    double z = get_point_z(a) + dz;
    set_point_x(a, x);
    set_point_y(a, y);
    set_point_z(a, z);
}

rc_type move_fig(figure& fig, const data& act)
{
    if (is_empty(fig))
        return ERR_EMPTY;

    double dx = get_deltax(act);
    double dy = get_deltay(act);
    double dz = get_deltaz(act);
    size_t n = get_fig_n(fig);

    for (size_t i = 0; i < n; i++)
    {
        move(get_point(fig, i), dx, dy, dz);
    }
    return OK;
}

void rotation_ax(point& a, double ax)
{
    double ya = get_point_y(a);
    double za = get_point_z(a);
    double alpha = ax * M_PI / 180;
    double cosax = cos(alpha);
    double sinax = sin(alpha);

    double z = za * cosax + ya * sinax;
    double y = ya * cosax - za * sinax;

    set_point_z(a, z);
    set_point_y(a, y);
}

void rotation_ay(point& a, double ay)
{
    double xa = get_point_x(a);
    double za = get_point_z(a);
    double alpha = ay * M_PI / 180;
    double cosay = cos(alpha);
    double sinay = sin(alpha);

    double x = xa * cosay + za * sinay;
    double z = za * cosay - xa * sinay;

    set_point_x(a, x);
    set_point_z(a, z);
}
void rotation_az(point& a, double az)
{
    double xa = get_point_x(a);
    double ya = get_point_y(a);
    double alpha = az * M_PI / 180;
    double cosaz = cos(alpha);
    double sinaz = sin(alpha);

    double x = xa * cosaz + ya * sinaz;
    double y = ya * cosaz - xa * sinaz;

    set_point_x(a, x);
    set_point_y(a, y);
}

void move_to_center(point& a, const point& center)
{
    a.x -= center.x;
    a.y -= center.y;
    a.z -= center.z;
}

void move_from_center(point& a, const point& center)
{
    a.x += center.x;
    a.y += center.y;
    a.z += center.z;
}

void rotation(point& a, const point& center, alpha_t alpha)
{
    move_to_center(a, center);
    double ax = get_alphax(alpha);
    double ay = get_alphay(alpha);
    double az = get_alphaz(alpha);
    if (az != 0)
    {
         rotation_az(a, az);
    }
    if (ax != 0)
    {
         rotation_ax(a, ax);
    }
    if (ay != 0)
    {
         rotation_ay(a, ay);
    }
    move_from_center(a, center);
}

rc_type rotation_fig(figure& fig, const data& act)
{
    if (is_empty(fig))
        return ERR_EMPTY;
    alpha_t alpha = get_alpha(act);

    point center;
    set_point(center, 0, 0, 0, 0);
    for (size_t i = 0; i < get_fig_n(fig); i++)
    {
        rotation(get_point(fig, i), center, alpha);
    }
    return OK;
}

void scale(point& a, const point& center, double k)
{
    double xc = get_point_x(center);
    double yc = get_point_y(center);
    double zc = get_point_z(center);

    double x = xc + k * (get_point_x(a) - xc);
    double y = yc + k * (get_point_y(a) - yc);
    double z = zc + k * (get_point_z(a) - zc);
    set_point_x(a, x);
    set_point_y(a, y);
    set_point_z(a, z);
}

rc_type scale_fig(figure& fig, const data& act)
{
    if (is_empty(fig))
        return ERR_EMPTY;

    double k = get_k(act);
    point center;
    set_point(center, 0, 0, 0, 0);
    for (size_t i = 0; i < get_fig_n(fig); i++)
    {
        scale(get_point(fig, i), center, k);
    }
    return OK;
}

rc_type draw_fig(figure& fig, myscene_t scene)
{
    clear_scene(scene);
    draw_model(fig, scene);
    return OK;
}

void draw_model(figure& fig, myscene_t scene)
{
    if (is_empty(fig))
        return;

    for (size_t i = 0; i < get_fig_n(fig); i++)
    {
        draw_point_scene(scene, get_point(fig, i));
    }

    size_t n = get_fig_n(fig);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            if (get_matrix_el(fig, i, j) != 0)
            {
                draw_line_scene(scene, get_point(fig, i), get_point(fig, j));
            }
        }
    }
}
