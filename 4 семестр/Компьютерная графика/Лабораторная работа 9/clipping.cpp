#include "clipping.h"

MathVector::MathVector(const int &x, const int &y, const int &z)
    : x_(x),
      y_(y),
      z_(z)
{
}

MathVector::MathVector(const QPoint &first, const QPoint &second)
{
    x_ = second.x() - first.x();
    y_ = second.y() - first.y();
    z_ = 0;
}

MathVector::MathVector(const QLine &line)
{
    QPoint first = line.p1();
    QPoint second = line.p2();
    x_ = second.x() - first.x();
    y_ = second.y() - first.y();
    z_ = 0;
}

int scalarMult(const MathVector &first, const MathVector &second)
{
    int res = first.x() * second.x() + first.y() * second.y() + first.z() * first.z();
    return res;
}

MathVector vectorMult(const MathVector &first, const MathVector &second)
{
    MathVector res;
    res.setX(first.y() * second.z() - first.z() * second.y());
    res.setY(first.z() * second.x() - first.x() * second.z());
    res.setZ(first.x() * second.y() - first.y() * second.x());
    return res;
}

int sign(const MathVector &cur_vector)
{
    if (cur_vector.z() > 0)
        return 1;
    else if (cur_vector.z() < 0)
        return -1;
    return 0;
}

int isConvex(const QVector<QPoint> &clip)
{
    int length = clip.size();
    QLine first = QLine(clip.back(), clip[0]);
    QLine second = QLine(clip[0], clip[1]);
    int cur, res;
    MathVector res_vector = vectorMult(first, second);
    res = sign(res_vector);
    for (int i = 1; i < length - 1; i++)
    {
        first = second;
        second = QLine(clip[i], clip[i + 1]);
        res_vector = vectorMult(first, second);
        cur = sign(res_vector);
        if (cur && cur != res)
        {
            return 0;
        }
    }
    return res;
}

QPoint countPoint(const QPoint &P1, const QPoint &P2, const double &t)
{
    QPoint res;
    res.setX(static_cast<int>(round((P1.x() + (P2.x() - P1.x()) * t))));
    res.setY(static_cast<int>(round(P1.y() + (P2.y() - P1.y()) * t)));
    return res;
}

int isVisible(const QPoint &P, const QPoint &C1, const QPoint &C2)
{
    MathVector C1P(C1, P);
    MathVector C1C2(C1, C2);
    MathVector res = vectorMult(C1P, C1C2);
    return sign(res);
}

bool hasIntersection(const QPoint &P1, const QPoint &P2, const QPoint &C1, const QPoint &C2)
{
    int vis_P1 = isVisible(P1, C1, C2);
    int vis_P2 = isVisible(P2, C1, C2);
    if ((vis_P1 > 0 && vis_P2 < 0) || (vis_P1 < 0 && vis_P2 > 0))
    {
        return true;
    }
    return false;
}

QPoint findIntersection(const QPoint &P1, const QPoint &P2, const QPoint &Q1, const QPoint &Q2)
{
    int A = P2.x() - P1.x();
    int B = Q1.x() - Q2.x();
    int C = Q1.x() - P1.x();
    int D = P2.y() - P1.y();
    int E = Q1.y() - Q2.y();
    int F = Q1.y() - P1.y();
    double det = A * E - B * D;
    double t = (C * E - B * F) / det;
    QPoint res = countPoint(P1, P2, t);
    return res;
}

bool findClippingPart(QVector<QPoint> clip, QVector<QPoint> &figure, const int orientation)
{
    int Nc = clip.size();
    int Na = figure.size();
    int Nb;
    QPoint F, S, I;
    QVector<QPoint> cur_figure;
    clip.push_back(clip[0]);
    for (int i = 0; i < Nc; i++)
    {
        Nb = 0;
        for (int j = 0; j < Na; j++)
        {
            if (j == 0)
            {
                F = figure[j];
            }
            else
            {
                bool pr = hasIntersection(S, figure[j], clip[i], clip[i + 1]);
                if (pr)
                {
                    I = findIntersection(S, figure[j], clip[i], clip[i + 1]);
                    cur_figure.push_back(I);
                    Nb++;
                }
            }
            S = figure[j];
            int wid = isVisible(S, clip[i], clip[i + 1]);
            if ((orientation > 0 && wid <= 0) || (orientation < 0 && wid >= 0))
            {
                cur_figure.push_back(S);
                Nb++;
            }
        }
        if (Nb == 0)
        {
            return false;
        }
        bool pr = hasIntersection(S, F, clip[i], clip[i + 1]);
        if (pr)
        {
            I = findIntersection(S, F, clip[i], clip[i + 1]);
            cur_figure.push_back(I);
            Nb++;
        }
        Na = Nb;
        figure = cur_figure;
        cur_figure.clear();
    }
    return true;
}

void drawClippedFigure(QPainter &painter, const QVector<QPoint> &clipped_figure)
{
    for (int i = 0; i < clipped_figure.size() - 1; i++)
    {
        painter.drawLine(clipped_figure[i], clipped_figure[i + 1]);
    }
    painter.drawLine(clipped_figure.back(), clipped_figure[0]);
}

bool SutherlandHodgman(QPainter &painter, const QVector<QPoint> &clip, const QVector<QPoint> &figure)
{
    int orientation = isConvex(clip);
    if (orientation != 0)
    {
        QVector<QPoint> clipped_figure = figure;
        bool draw = findClippingPart(clip, clipped_figure, orientation);
        if (draw)
        {
            drawClippedFigure(painter, clipped_figure);
        }
        return true;
    }
    return false;
}
