#ifndef ELLIPS_H
#define ELLIPS_H

#include <draw.h>

void canonicalEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2);
void parametricEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2);
void bresenhamEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2);
void midPointEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2);


#endif // ELLIPS_H
