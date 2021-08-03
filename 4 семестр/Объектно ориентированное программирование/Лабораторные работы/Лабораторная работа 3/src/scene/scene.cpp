#include "scene.h"

void Scene::accept(Visitor &visitor)
{
    for (const auto &elem : *objects)
        elem->accept(visitor);
}

void Scene::conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate)
{
    for (auto &object : *objects)
        object->conversion(transfer, scale, rotate);
}

