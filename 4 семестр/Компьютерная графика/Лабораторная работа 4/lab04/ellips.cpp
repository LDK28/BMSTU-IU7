#include "ellips.h"

void canonicalEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag)
{
    for (long x = 0; x <= r1; ++x)
    {
        long y = round(r2 * sqrt(1.0 - x * x / r1 / r1));
        if (flag)
            draw(scene, color, cx, cy, x, y);
    }

    for (long y = 0; y <= r2; ++y)
    {
        long x = round(r1 * sqrt(1.0 - y * y / r2 / r2));
        if (flag)
            draw(scene, color, cx, cy, x, y);
    }
}

void parametricEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag)
{

    double m = fmax(r1, r2);
    long l = round(M_PI * m / 2);
    for (long i = 0; i <= l; ++i)
    {
        long x = round(r1 * cos(i / m));
        long y = round(r2 * sin(i / m));

        if (flag)
            draw(scene, color, cx, cy, x, y);
    }
}

void bresenhamEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag)
{
    long x = 0;
    long y = r2;
    r1 = r1 * r1;
    long d = round(r2 * r2 / 2 - r1 * r2 * 2 + r1 / 2);
    r2 = r2 * r2;

    while (y >= 0)
    {
        if (flag)
            draw(scene, color, cx, cy, x, y);

        if (d < 0) //пиксель лежит внутри эллипса
        {
            double buf = 2 * d + 2 * r1 * y - r2;
            ++x;
            if (buf <= 0)  // горизотальный шаг
                d = d + 2 * r2 * x + r2;
            else  // диагональный шаг
            {
                --y;
                d = d + 2 * r2 * x - 2 * r1 * y + r1 + r2;
            }

            continue;
        }
        if (d > 0)  // пиксель лежит вне эллипса
        {
            double buf = 2 * d - 2 * r2 * x - r2;
            --y;

            if (buf > 0)  // вертикальный шаг
                d = d - 2 * y * r1 + r1;
            else  // диагональный шаг
            {
                ++x;
                d = d + 2 * x * r2 - 2 * y * r1 + r1 + r2;
            }

            continue;
        }

        if (d == 0)  // пиксель лежит на окружности
        {
            ++x; //диагональный шаг
            --y;
            d = d + 2 * x * r2 - 2 * y * r1 + r1 + r2;
        }
    }
}

void midPointEllips(QGraphicsScene *scene, QPen color, double cx, double cy, double r1, double r2, int flag)
{
    long x = 0; // начальные положения
    long y = r2;

    double a = r1*r1;
    double b = r2*r2;
    double ad = a * 2;
    double bd = b * 2;

    double x_max = a / sqrt(a + b);
    double teta = -ad * y;
    double dx = 0;

    double fpr = b - a * y + a * 0.25;

    while (x < x_max)
    {
        if (flag)
            draw(scene, color, cx, cy, x, y);

        if (fpr > 0)
        {
            --y;
            teta += ad;
            fpr += teta;
        }

        dx += bd;
        ++x;
        fpr += dx + b;
    }

    fpr += 0.75 * (a - b) - (b * x + a * y);

    teta = bd * x;
    double dy = -ad * y;

    while (y >= 0)
    {
        if (flag)
            draw(scene, color, cx, cy, x, y);
        if (fpr < 0)
        {
            ++x;
            teta += bd;
            fpr += teta;
        }

        dy += ad;
        fpr += dy + a;
        --y;
    }
}
