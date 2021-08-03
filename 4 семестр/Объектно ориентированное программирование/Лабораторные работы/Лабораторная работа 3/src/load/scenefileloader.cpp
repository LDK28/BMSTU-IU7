#include "scenefileloader.h"

SceneFileLoader::SceneFileLoader()
{
    stream = shared_ptr<ifstream>(new ifstream);
    builder = shared_ptr<BaseSceneBuilder>(new SceneBuilder);
}

SceneFileLoader::SceneFileLoader(const shared_ptr<ifstream> &_stream)
{
    stream = _stream;
    builder = shared_ptr<BaseSceneBuilder>(new SceneBuilder);
}

void SceneFileLoader::open(const string &file_name)
{
    if (stream->is_open())
        close();

    stream->open(file_name);

    if (!stream->is_open())
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(BaseSourceLoader).name(), __FUNCTION__);
    }
}

void SceneFileLoader::close()
{
    stream->close();
}

void SceneFileLoader::read_objects(vector<shared_ptr<Object>> &objects, shared_ptr<BaseSourceLoader> &loader)
{
    int count = read_number();
    for (int i = 0; i < count; i++)
        objects.push_back(loader->load());
}

int BaseSceneLoader::read_number()
{
    int num;
    if (!(*stream >> num))
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(BaseSourceLoader).name(), __FUNCTION__);
    }

    return num;
}

shared_ptr<Scene> SceneFileLoader::load()
{
    builder->reset();

    if (stream->is_open())
    {
        shared_ptr<BaseSourceLoader> figureLoader = shared_ptr<BaseSourceLoader>(new FigureFileLoader(stream));
        shared_ptr<BaseSourceLoader> cameraLoader = shared_ptr<BaseSourceLoader>(new CameraFileLoader(stream));

        vector<shared_ptr<Object>> objects;

        read_objects(objects, figureLoader);
        read_objects(objects, cameraLoader);

        builder->build_objects(objects);
    }
    else
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(SceneFileLoader).name(), __FUNCTION__);
    }

    return builder->get_result();
}
