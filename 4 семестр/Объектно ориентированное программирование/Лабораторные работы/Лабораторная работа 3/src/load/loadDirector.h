#ifndef LOADDIRECTOR_H
#define LOADDIRECTOR_H

#include "objects/object.h"
#include "basesourceloader.h"
#include <string>
#include "configuration/loadsolution.h"


class LoadDirector
{
public:
    LoadDirector() = default;
    ~LoadDirector() = default;

    virtual shared_ptr<Object> load(const string &file_name) = 0;
protected:
    shared_ptr<BaseSourceLoader> loader;
};

class FigureDirector : public LoadDirector
{
public:
    FigureDirector() = default;
    ~FigureDirector() = default;

    virtual shared_ptr<Object> load(const string &file_name) override;
};

class SceneDirector
{
public:
    SceneDirector() = default;
    ~SceneDirector() = default;

    shared_ptr<Scene> load(const string &file_name);
};

class CameraDirector : public LoadDirector
{
public:
    CameraDirector() = default;
    ~CameraDirector() = default;

    virtual shared_ptr<Object> load(const string &file_name) override;
};

#endif // LOADDIRECTOR_H
