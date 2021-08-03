#ifndef BASEVISITOR_H
#define BASEVISITOR_H

class Figure;
class Camera;
class Composite;
class Scene;

class BaseVisitor
{
    public:
    BaseVisitor() = default;
    ~BaseVisitor() = default;

    virtual void visit(Figure &figure) = 0;
    virtual void visit(const Composite &composite) = 0;
    virtual void visit(const Scene &scene) = 0;
};

#endif // BASEVISITOR_H
