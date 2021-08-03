#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H

#include "../objects/camera.h"

class BaseCameraBuilder
{
    public:
    BaseCameraBuilder() = default;
    ~BaseCameraBuilder() = default;

    virtual bool is_build() = 0;
    virtual void reset() = 0;

    virtual void build_position(const Point &position) = 0;
    virtual void build_direction(const Point &direction) = 0;

    virtual shared_ptr<Object> get_result() = 0;

protected:
    Point position, direction;
    bool is_position, is_direction;
};

class CameraBuilder : public BaseCameraBuilder
{
public:
    CameraBuilder() = default;
    ~CameraBuilder() = default;

    virtual bool is_build() override {return is_position && is_direction; };
    virtual void reset() override {is_position = is_direction = false; };

    virtual void build_position(const Point &_position) override {position = _position; is_position = true; };
    virtual void build_direction(const Point &_direction) override {direction = _direction; is_direction = true; };

    virtual shared_ptr<Object> get_result() override;
};

#endif // CAMERABUILDER_H
