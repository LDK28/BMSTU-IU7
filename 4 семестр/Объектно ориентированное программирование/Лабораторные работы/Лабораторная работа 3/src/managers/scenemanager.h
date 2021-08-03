#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "basemanager.h"
#include "scene/scene.h"

class SceneManager : public BaseManager
{
public:
    SceneManager();

    shared_ptr<Scene> get_scene() const {return scene; };
    void set_scene(shared_ptr<Scene> &_scene) {scene = _scene; };

    shared_ptr<Object> get_camera() const;
    void set_camera(int index);
    void set_camera(const IteratorObject &it);
private:
    shared_ptr<Scene> scene;
    std:: weak_ptr<Object> camera;
};

class SceneManagerCreator
{
public:
    std::shared_ptr<SceneManager> get_manager();
private:
    void create_manager();

    std::shared_ptr<SceneManager> manager;
};

#endif // SCENEMANAGER_H
