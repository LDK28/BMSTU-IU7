#include "loadDirector.h"

shared_ptr<Object> FigureDirector::load(const string &file_name)
{
    shared_ptr<BaseSourceLoader> loader = FigureLoadSolution().get_creator()->create();

    loader->open(file_name);

    shared_ptr<Object> figure = loader->load();

    loader->close();

    return figure;
}

shared_ptr<Scene> SceneDirector::load(const string &file_name)
{
    shared_ptr<BaseSceneLoader> loader = SceneLoadSolution().get_creator()->create();

    loader->open(file_name);

    shared_ptr<Scene> scene = loader->load();

    loader->close();

    return scene;
}

shared_ptr<Object> CameraDirector::load(const string &file_name)
{
    shared_ptr<BaseSourceLoader> loader = CameraLoadSolution().get_creator()->create();

    loader->open(file_name);

    shared_ptr<Object> camera = loader->load();

    loader->close();

    return camera;
}
