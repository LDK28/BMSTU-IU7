#ifndef LOADSOUTION_H
#define LOADSOUTION_H

#include <memory>
#include "load/loadcreator.h"
#include "managers/configmanager.h"

class FigureLoadSolution
{
public:
    FigureLoadSolution() = default;

    shared_ptr<LoadCreator> get_creator();
};

class SceneLoadSolution
{
public:
    SceneLoadSolution() = default;

    shared_ptr<SceneLoadCreator> get_creator();
};

class CameraLoadSolution
{
public:
    CameraLoadSolution() = default;

    shared_ptr<LoadCreator> get_creator();
};

#endif // LOADSOUTION_H
