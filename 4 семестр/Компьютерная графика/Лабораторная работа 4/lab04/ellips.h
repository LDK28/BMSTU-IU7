#ifndef ELLIPS_H
#define ELLIPS_H

#include <draw.h>

void canonicalEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag);
void parametricEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag);
void bresenhamEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag);
void midPointEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag);


#endif // ELLIPS_H
