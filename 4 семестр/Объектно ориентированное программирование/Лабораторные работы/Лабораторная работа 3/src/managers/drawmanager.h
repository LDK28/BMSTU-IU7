#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "basemanager.h"
#include "abstractfactory/drawer.h"
#include "objects/camera.h"
#include "scenemanager.h"

class DrawManager : public BaseManager
{
public:
    DrawManager() : scene(SceneManagerCreator().get_manager()->get_scene()) {};
    ~DrawManager() = default;

    void draw(const shared_ptr<BaseDrawer> &drawer, const shared_ptr<Camera> &camera);
private:
    shared_ptr<Scene> scene;
    shared_ptr<Visitor> visitor;
};

class DrawManagerCreator
{
public:
    std::shared_ptr<DrawManager> get_manager();
private:
    void create_manager();

    std::shared_ptr<DrawManager> manager;
};
#endif // DRAWMANAGER_H
