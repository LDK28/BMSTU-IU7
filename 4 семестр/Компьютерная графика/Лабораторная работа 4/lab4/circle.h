#ifndef CIRCLE_H
#define CIRCLE_H

#include <draw.h>

void canonicalCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r);
void parametricCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r);
void bresenhamCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r);
void midPointCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r);


#endif // CIRCLE_H
