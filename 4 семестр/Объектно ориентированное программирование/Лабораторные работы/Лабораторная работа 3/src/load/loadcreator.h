#ifndef LOADCREATOR_H
#define LOADCREATOR_H

#include <memory>
#include "basesourceloader.h"
#include "scenefileloader.h"
#include "figurefileloader.h"
#include "camerafileloader.h"


class LoadCreator
{
public:
    LoadCreator() = default;
    ~LoadCreator() = default;

    virtual shared_ptr<BaseSourceLoader> create() = 0;
};

class FigureLoadCreator : public LoadCreator
{
public:
    FigureLoadCreator() = default;
    ~FigureLoadCreator() = default;

    virtual shared_ptr<BaseSourceLoader> create() override {return shared_ptr<FigureFileLoader>(new FigureFileLoader); };
};

class SceneLoadCreator
{
public:
    SceneLoadCreator()  = default;
    ~SceneLoadCreator() = default;

    shared_ptr<BaseSceneLoader> create() {return shared_ptr<BaseSceneLoader>(new SceneFileLoader); };
};

class CameraLoadCreator : public LoadCreator
{
public:
    CameraLoadCreator() = default;
    ~CameraLoadCreator() = default;

    virtual shared_ptr<BaseSourceLoader> create() override {return shared_ptr<CameraFileLoader>(new CameraFileLoader); };
};

#endif // LOADCREATOR_H
