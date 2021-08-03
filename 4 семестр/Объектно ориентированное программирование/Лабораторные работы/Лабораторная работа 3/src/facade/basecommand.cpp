#include "basecommand.h"

void DrawScene::execute()
{
    shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(SceneManagerCreator().get_manager()->get_camera());

    if (camera == nullptr)
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw camera_exception(ctime(&timenow), __FILE__, typeid(DrawScene).name(), __FUNCTION__);
    }
    DrawManagerCreator().get_manager()->draw(drawer, camera);
}

void SetCamera::execute()
{
    SceneManagerCreator().get_manager()->set_camera(camera);
}

void LoadScene::execute()
{
    shared_ptr<Scene> scene = LoadManagerCreator().get_manager()->load_scene(file_name);
    SceneManagerCreator().get_manager()->set_scene(scene);
}

void LoadCamera::execute()
{
    shared_ptr<Object> camera = LoadManagerCreator().get_manager()->load_camera(file_name);
    SceneManagerCreator().get_manager()->get_scene()->add_object(camera);
}

void LoadFigure::execute()
{
    shared_ptr<Object> figure = LoadManagerCreator().get_manager()->load_figure(file_name);
    SceneManagerCreator().get_manager()->get_scene()->add_object(figure);
}

void AddObject::execute()
{
    SceneManagerCreator().get_manager()->get_scene()->add_object(object);
}

void RemoveObject::execute()
{
    SceneManagerCreator().get_manager()->get_scene()->remove_object(index);
}

void TransferObject::execute()
{
    ScaleCoef scale(1,1,1);
    Angle rotate(0, 0, 0);

    shared_ptr<Object> object = *((SceneManagerCreator().get_manager()->get_scene()->get_objects()->begin()) + index);
    object->conversion(transfer, scale, rotate);
}

void ScaleObject::execute()
{
    Point transfer(0,0,0);
    Angle rotate(0, 0, 0);

    shared_ptr<Object> object = *((SceneManagerCreator().get_manager()->get_scene()->get_objects()->begin()) + index);
    object->conversion(transfer, scale, rotate);
}

void RotateObject::execute()
{
    ScaleCoef scale(1,1,1);
    Point transfer(0, 0, 0);

    shared_ptr<Object> object = *((SceneManagerCreator().get_manager()->get_scene()->get_objects()->begin()) + index);
    object->conversion(transfer, scale, rotate);
}

