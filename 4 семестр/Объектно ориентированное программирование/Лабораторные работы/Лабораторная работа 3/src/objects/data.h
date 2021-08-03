#ifndef DATA_H
#define DATA_H

#include "point.h"
#include "edge.h"

#include <vector>

using namespace std;

class Data
{
public:
    Data() = default;
    void add_point(double x, double y, double z) {points.push_back(Point(x, y, z)); };
    void add_point(const Point &point) {points.push_back(point); };
    void add_edge(int first, int second) {edges.push_back(Edge(first, second)); };
    void add_edge(const Edge &edge) {edges.push_back(edge); };
    void add_center(double x, double y, double z) {center = Point(x, y, z); };
    void add_center(const Point &point) {center = point; };

    void transfer(const Point &transfer);
    void rotate(const Angle &angle);
    void scale(const ScaleCoef &scale);

    const vector<Point> &get_points() const {return points; };
    const vector<Edge> &get_edges() const {return edges; };

    void clear() {points.clear(); edges.clear(); };
private:
    vector<Point> points;
    vector<Edge> edges;
    Point center;
};

#endif // DATA_H
