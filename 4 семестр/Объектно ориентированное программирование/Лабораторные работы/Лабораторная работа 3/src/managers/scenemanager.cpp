#include "scenemanager.h"

SceneManager::SceneManager()
{
}


void SceneManagerCreator::create_manager()
{
    static shared_ptr<SceneManager>_manager(new SceneManager);
    manager = _manager;
}

shared_ptr<SceneManager> SceneManagerCreator::get_manager()
{
    if (manager == nullptr)
        create_manager();

    return manager;
}

void SceneManager::set_camera(int index)
{
    IteratorObject it = scene->get_objects()->begin() + index;
    set_camera(it);
}

void SceneManager::set_camera(const IteratorObject &it)
{
    if (it != scene->get_objects()->end())
    {
        camera = (*it);
    }
}

shared_ptr<Object> SceneManager::get_camera() const
{
    return camera.lock();
}
