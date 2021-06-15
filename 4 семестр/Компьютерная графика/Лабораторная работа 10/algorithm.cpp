#include "algorithm.h"

#include <algorithm>
#include <cmath>
#include <QVector3D>

template <typename T>
constexpr T sgn(T value) {
    if (value < T(0))
        return T(-1);
    if (value > T(0))
        return T(1);
    return T(0);
}

void intersect(int &xi, int &yi, int x1, int y1, int x2, int y2, const QVector<int> &horizon)
{
    const auto h1 = horizon[x1];
    const auto h2 = horizon[x2];

    const auto delta_x = x2 - x1;
    const auto delta_y = y2 - y1;
    const auto delta_h = h2 - h1;

    if (!delta_x) {
        xi = x2;
        yi = h2;
        return;
    }

    if (y1 == h1 && y2 == h2) {
        xi = x1;
        yi = y1;
        return;
    }

    const auto m = static_cast<double>(delta_y) / delta_x;

    xi = x1 - qRound(static_cast<double>(delta_x * (y1 - h1)) / (delta_y - delta_h));
    yi = qRound((xi - x1) * m + y1);
}

void horizon(QPainter &painter, QVector<int> &top, QVector<int> &down, int x1, int y1, int x2, int y2)
{
    if (x2 < x1) {
        qSwap(x1, x2);
        qSwap(y1, y2);
    }

    if (x2 == x1) {
        top[x2] = qMax(top[x2], y2);
        down[x2] = qMin(down[x2], y2);
        if (0 <= x2  && x2 <= 720)
            painter.drawLine(x1, y1, x2, y2);
    }
    else {
        const auto xp = x1;
        const auto yp = y1;
        const auto m = static_cast<double>(y2 - y1) / (x2 - x1);

        for (int x = x1; x <= x2; ++x) {
            const auto y = qRound(m * (x - x1) + y1);
            top[x] = qMax(top[x], y);
            down[x] = qMin(down[x], y);

            if (0 <= x && x <= 720)
                painter.drawLine(xp, yp, x, y);
        }
    }
}

void processEdge(QPainter &painter, int &x, int &y, int &xEdge, int &yEdge, QVector<int> &top, QVector<int> &down)
{
    if (~xEdge)
        horizon(painter, top, down, xEdge, yEdge, x , y);

    xEdge = x;
    yEdge = y;
}

int visible(int x, int y, const QVector<int> &top, const QVector<int> &down)
{
    if (y >= top[x])
        return 1;
    if (y <= down[x])
        return -1;
    return 0;
}

void rotate(double &x, double &y, double phi)
{
    phi *= M_PI / 180.0;
    const auto __x = x;
    const auto __y = y;
    const auto __c = std::cos(phi);
    const auto __s = std::sin(phi);
    x = __c * __x - __s * __y;
    y = __c * __y + __s * __x;
}

double transform(int &tx, int &ty, double x, double y, double z, double phi_x, double phi_y, double phi_z, int zoom)
{
    const auto xc = 360;
    const auto yc = 360;

    rotate(y, z, phi_x);
    rotate(x, z, phi_y);
    rotate(x, y, phi_z);

    tx = qRound(x * zoom + xc);
    ty = qRound(y * zoom + yc);

    return z;
}

QVector<QVector<QVector3D>> dots(const Function &function, const FunctionData &data, int zoom) {
    QVector<QVector<QVector3D>> result;

    for (auto z = data.ze; z >= data.zb; z -= data.dz) {
        QVector<QVector3D> line;
        for (double x = data.xb; x <= data.xe; x += data.dx) {
            const double y = function(x, z);

            int xt, yt;
            double zt = transform(xt, yt, x, y, z, data.phi_x, data.phi_y, data.phi_z, zoom);
            line.push_back(QVector3D(xt, yt, zt));
        }
        result.push_back(line);
    }

    if (result.front().front().z() < result.back().front().z())
        std::reverse(result.begin(), result.end());

    return result;
}

void FloatingHorizonAlgorithm(QPainter &painter, const Function &function, const FunctionData &data, int zoom)
{
    const auto surface = dots(function, data, zoom);

    QVector<int> top(720, 0);
    QVector<int> down(720, 720);

    int xl = -1;
    int xr = -1;
    int yl = -1;
    int yr = -1;

    for (int i = 0; i < surface.size(); ++i) {
        int xp = surface[i][0].x();
        int yp = surface[i][0].y();
        processEdge(painter, xp, yp, xl, yl, top, down);
        auto pflag = visible(xp, yp, top, down);

        for (int j = 0; j < surface[i].size(); ++j) {
            int xc = surface[i][j].x();
            int yc = surface[i][j].y();
            int xi, yi;
            auto tflag = visible(xc, yc, top, down);

            if (tflag == pflag) {
                if (pflag)
                    horizon(painter, top, down, xp, yp, xc, yc);
            }
            else if (!tflag) {
                intersect(xi, yi, xp, yp, xc, yc, pflag == 1 ? top : down);
            }
            else if (tflag == 1) {
                intersect(xi, yi, xp, yp, xc, yc, top);
                horizon(painter, top, down, xp, yp, xi, yi);

                if (pflag) {
                    intersect(xi, yi, xp, yp, xc, yc, down);
                    horizon(painter, top, down, xp, yp, xi, yi);
                }
            }
            else {
                intersect(xi, yi, xp, yp, xc, yc, down);
                horizon(painter, top, down, xp, yp, xi, yi);

                if (pflag) {
                    intersect(xi, yi, xp, yp, xc, yc, top);
                    horizon(painter, top, down, xp, yp, xi, yi);
                }
            }

            pflag = tflag;
            xp = xc;
            yp = yc;
        }
        processEdge(painter, xp, yp, xr, yr, top, down);
    }

}
