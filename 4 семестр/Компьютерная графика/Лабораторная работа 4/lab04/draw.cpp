#include "draw.h"

void draw(QGraphicsScene *scene, QPen color, long cx, long cy, long x, long y)
{
    scene->addEllipse(cx + x, cy + y, 1, 0, color);
    scene->addEllipse(cx + x, cy - y, 1, 0, color);
    scene->addEllipse(cx - x, cy + y, 1, 0, color);
    scene->addEllipse(cx - x, cy - y, 1, 0, color);
}
