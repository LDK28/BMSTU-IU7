#ifndef CLIPPING_H
#define CLIPPING_H

#include <QPainter>
#include <cmath>

class MathVector
{
public:
    MathVector() {}
    MathVector(const int &x, const int &y, const int &z = 0);
    MathVector(const QPoint &first, const QPoint &second);
    MathVector(const QLine &line);
    int x() const { return x_; }
    int y() const { return y_; }
    int z() const { return z_; }
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }
    void setZ(int z) { z_ = z; }
private:
    int x_;
    int y_;
    int z_;
};

bool SutherlandHodgman(QPainter &painter, const QVector<QPoint> &clip, const QVector<QPoint> &figure);
#endif // CLIPPING_H
