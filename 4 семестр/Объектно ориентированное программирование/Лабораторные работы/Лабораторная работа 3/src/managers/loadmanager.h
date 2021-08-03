#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include "basemanager.h"
#include "load/loaddirector.h"
#include "scene/scene.h"

class LoadManager : public BaseManager
{
public:
    LoadManager();

    shared_ptr<Object> load_figure(const string &file_name) {return figure_loader->load(file_name); };
    shared_ptr<Scene> load_scene(const string &file_name) {return scene_loader->load(file_name); };
    shared_ptr<Object> load_camera(const string &file_name) {return camera_loader->load(file_name); };
private:
    shared_ptr<LoadDirector> figure_loader;
    shared_ptr<SceneDirector> scene_loader;
    shared_ptr<LoadDirector> camera_loader;
};

class LoadManagerCreator
{
public:
    std::shared_ptr<LoadManager> get_manager();
private:
    void create_manager();

    std::shared_ptr<LoadManager> manager;
};

#endif // LOADMANAGER_H
