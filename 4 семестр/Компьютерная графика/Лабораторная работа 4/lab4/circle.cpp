#include "circle.h"

void canonicalCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r)
{
    for (long x = 0; x <= r; ++x)
    {
        long y = round(sqrt(r * r - x * x));
        draw(scene, color, cx, cy, x, y);
    }

    for (long y = 0; y <= r; ++y)
    {
        long x = round(sqrt(r * r - y * y));
        draw(scene, color, cx, cy, x, y);
    }
}

void parametricCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r)
{

    long l = round(M_PI * r / 2);
    for (long i = 0; i <= l; ++i)
    {
        long x = round(r * cos(i / r));
        long y = round(r * sin(i / r));

        draw(scene, color, cx, cy, x, y);
    }
}

void bresenhamCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r)
{
    long x = 0;
    double y = r;
    double d = 2 - 2 * r; // D(x+1, y-1) = [(x + 1)^2 + (y - 1)^2] - R^2 при x = 0, y = R // [...] - квадрат расстояния от центра, до диаг. точки

    while (y >= 0)
    {
        draw(scene, color, cx, cy, x, y);

        if (d < 0)  // пиксель лежит внутри окружности
        {
            double b = 2 * d + 2 * y - 1;
            ++x;

            if (b <= 0)  // горизонтальный шаг
                d = d + 2 * x + 1;
            else  // диагональный шаг
            {
                --y;
                d = d + 2 * x - 2 * y + 2;
            }

            continue;
        }
        if (d > 0)  // пиксель лежит вне окружности
        {
            double b = 2 * d - 2 * x - 1;
            --y;

            if (b > 0)  // вертикальный шаг
                d = d - 2 * y + 1;
            else  // диагональный шаг
            {
                ++x;
                d = d + 2 * x - 2 * y + 2;
            }

            continue;
        }
        if (d == 0)  // пиксель лежит на окружности
        {
            ++x;  // диагональный шаг
            --y;
            d = d + 2 * x - 2 * y + 2;
        }
    }
}

void midPointCircle(QGraphicsScene *scene, QPen color, double cx, double cy, double r)
{

    long x = 0;
    double y = r;
    double p = 1 - r;  // (x + 1)^2 + (y - 1/2)^2 - r^2 // p = (x + 1)^2 + (y - 1/2)^2 - r^2
    draw(scene, color, cx, cy, x, y);
    draw(scene, color, cx, cy, y, x);

    while (x < y)
    {
        ++x;
        if (p < 0)  // средняя точка внутри окружности, ближе верхний пиксел, горизонтальный шаг
            p += 2 * x + 1;
        else   // средняя точка вне окружности, ближе диагональный пиксел, диагональный шаг
        {
            --y;
            p += 2 * x - 2 * y + 1;
        }

        draw(scene, color, cx, cy, x, y);
        draw(scene, color, cx, cy, y, x);
    }
}
