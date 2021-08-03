#ifndef VISITOR_H
#define VISITOR_H

#include "../Mathobj/pixel.h"
#include "../objects/edge.h"
#include "../objects/point.h"
#include <memory>
#include <vector>
#include "objects/figure.h"
#include "objects/camera.h"
#include "../objects/data.h"
#include "../visitor/baseVisitor.h"
#include "../abstractfactory/drawer.h"

using namespace std;

class Figure;
class Camera;
class Composite;
class Scene;

class Visitor : public BaseVisitor
{
public:
    Visitor() = delete;
    Visitor(const shared_ptr<Camera> &_camera) : camera(_camera) {};
    ~Visitor() = default;

    void visit(Figure &figure);
    void visit(const Composite &composite);
    void visit(const Scene &scene);

    const vector<Pixel> &get_pixels() const {return points; };
    const vector<Edge> &get_edges() const {return edges; };
private:
    Pixel proect_point(const Point &point);

private:
    shared_ptr<Camera> camera;
    vector<Pixel> points;
    vector<Edge> edges;
};

#endif // VISITOR_H
