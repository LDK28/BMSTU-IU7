#ifndef MESCENE_H
#define MESCENE_H
#include <QGraphicsScene>
#include "rc.h"
#include "points.h"

typedef struct myscene myscene_t;

struct myscene
{
    QGraphicsScene *scene;
};


rc_type draw_line_scene(myscene_t scene, const point& p1, const point& p2);
void draw_point_scene(myscene_t scene, const point& p1);
void clear_scene(myscene_t scene);

#endif
