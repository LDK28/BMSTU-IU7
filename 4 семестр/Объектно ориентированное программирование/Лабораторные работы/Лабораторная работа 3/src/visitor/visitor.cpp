#include "visitor.h"

#include <math.h>

Pixel Visitor::proect_point(const Point &point)
{
    int x = point.get_x();
    int y = point.get_y();
    int z = point.get_z();

    int x_p = x - camera->get_pos().get_x();
    int y_p = y - camera->get_pos().get_y();
    int z_p = z - camera->get_pos().get_z();

    return Pixel(x_p - z_p / sqrt(2.0) + 300, y_p - z_p / sqrt(2.0)  + 300);
}


void Visitor::visit(Figure &figure)
{
    const Data data = figure.get_data();

    const vector<Point> _points = data.get_points();
    const vector<Edge> _edges = data.get_edges();

    for (const auto &edge : _edges)
        edges.push_back(edge);

    for (const auto &point : _points)
        points.push_back(proect_point(point));
}

void Visitor::visit(const Composite &composite)
{

}

void Visitor::visit(const Scene &scene)
{

}
