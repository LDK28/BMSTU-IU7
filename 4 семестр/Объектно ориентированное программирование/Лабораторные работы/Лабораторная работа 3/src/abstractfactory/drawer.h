#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsScene>
#include "../objects/point.h"
#include "../Mathobj/pixel.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    ~BaseDrawer() = default;

    virtual void clear() = 0;
    virtual void add_line(const Pixel &fst, const Pixel &scd) = 0;
};

class Drawer : public BaseDrawer
{
public:
    Drawer() = default;
    ~Drawer() = default;

    Drawer(std::shared_ptr<QGraphicsScene> _scene) : scene(_scene) {};


    virtual void clear() override {scene->clear(); };
    virtual void add_line(const Pixel &fst, const Pixel &scd) override {scene->addLine(fst.get_x(), fst.get_y(), scd.get_x(), scd.get_y()); };

private:
    std::shared_ptr<QGraphicsScene> scene;
};

#endif // DRAWER_H
