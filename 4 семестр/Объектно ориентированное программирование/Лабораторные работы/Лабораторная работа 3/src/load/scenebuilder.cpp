#include "scenebuilder.h"

void SceneBuilder::build_objects(std::vector<shared_ptr<Object>> &objects)
{
    for (auto &object : objects)
        scene->add_object(object);
}

shared_ptr<Scene> SceneBuilder::get_result()
{
    return scene;
}
