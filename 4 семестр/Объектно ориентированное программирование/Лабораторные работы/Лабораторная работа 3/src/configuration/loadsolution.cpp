#include "loadsolution.h"

shared_ptr<LoadCreator> FigureLoadSolution::get_creator()
{
    return ConfigManagerCreator().get_manager()->get_creator(0);
}

shared_ptr<SceneLoadCreator> SceneLoadSolution::get_creator()
{
    return shared_ptr<SceneLoadCreator>(new SceneLoadCreator);
}

shared_ptr<LoadCreator> CameraLoadSolution::get_creator()
{
    return ConfigManagerCreator().get_manager()->get_creator(1);
}
