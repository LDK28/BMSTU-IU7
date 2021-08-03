#include "loadmanager.h"

LoadManager::LoadManager()
{
    figure_loader = shared_ptr<LoadDirector>(new FigureDirector);
    scene_loader = shared_ptr<SceneDirector>(new SceneDirector);
    camera_loader = shared_ptr<LoadDirector>(new CameraDirector);
}

void LoadManagerCreator::create_manager()
{
    static shared_ptr<LoadManager>_manager(new LoadManager);
    manager = _manager;
}

shared_ptr<LoadManager> LoadManagerCreator::get_manager()
{
    if (manager == nullptr)
        create_manager();

    return manager;
}
