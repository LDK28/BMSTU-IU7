#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"
#include "point.h"
#include "../Mathobj/mathobjs.h"

class InvisibleObject;

class Camera : public InvisibleObject
{
public:
    Camera() = default;
    Camera(const Point &_position, const Point &_direction) {position = _position; direction = _direction; };
    ~Camera() = default;

    virtual void conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate) override;
    virtual void accept(Visitor &visitor) override;

    friend class Visitor;

protected:
    Point get_direction() const {return direction; };
    Point get_pos() const {return position; };

private:
    void transfer(const Point &transfer) {position.transfer(transfer); };
    void rotate(const Angle &rotate) {direction.rotate(Point(0,0,0), rotate); };

    Point position;
    Point direction;
};

#endif // CAMERA_H
