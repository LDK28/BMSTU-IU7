#include "figurebuilder.h"

void FigureBuilder::build_center(Point &center)
{
    data.add_center(center);

    is_center = true;
}

void FigureBuilder::build_edges(vector<Edge> &edges)
{
    for (const auto &edge : edges)
        data.add_edge(edge);

    is_edges = true;
}

void FigureBuilder::build_points(vector<Point> &points)
{
    for (const auto &point : points)
        data.add_point(point);

    is_edges = true;
}

std::shared_ptr<Object> FigureBuilder::get_result()
{
    return std::shared_ptr<Object>(new Figure(data));
}
