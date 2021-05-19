#ifndef CIRCLE_H
#define CIRCLE_H

#include <draw.h>

void canonicalCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r, int flag);
void parametricCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r, int flag);
void bresenhamCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r, int flag);
void midPointCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r, int flag);


#endif // CIRCLE_H
