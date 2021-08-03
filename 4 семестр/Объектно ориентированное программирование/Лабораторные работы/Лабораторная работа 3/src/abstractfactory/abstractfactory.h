#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <memory>
#include "drawer.h"

using namespace std;

class AbstractFactory
{
public:
    AbstractFactory() = default;
    ~AbstractFactory() = default;

    virtual shared_ptr<BaseDrawer> create() = 0;
};

class Factory : public AbstractFactory
{
public:
    Factory(shared_ptr<QGraphicsScene> _scene) : scene(_scene) {};
    ~Factory() = default;

    virtual shared_ptr<BaseDrawer> create() override { return shared_ptr<BaseDrawer>(new Drawer(scene)); };
private:
    shared_ptr<QGraphicsScene> scene;
};

#endif // ABSTRACTFACTORY_H
