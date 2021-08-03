#include "camerafileloader.h"

CameraFileLoader::CameraFileLoader()
{
    builder = shared_ptr<BaseCameraBuilder>(new CameraBuilder);
    stream = shared_ptr<ifstream>(new ifstream);
}

CameraFileLoader::CameraFileLoader(const shared_ptr<ifstream> &_stream)
{
    builder = shared_ptr<BaseCameraBuilder>(new CameraBuilder);
    stream = _stream;
}

void CameraFileLoader::open(const string &file_name)
{
    if (stream->is_open())
        close();
    stream->open(file_name);

    if (!stream)
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(BaseSourceLoader).name(), __FUNCTION__);
    }
}

void CameraFileLoader::close()
{
    stream->close();
}

std::shared_ptr<Object> CameraFileLoader::load()
{
    builder->reset();
    if (stream->is_open())
    {
        builder->build_position(read_point());
        builder->build_direction(read_point());
    }
    else
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(CameraFileLoader).name(), __FUNCTION__);
    }

    return builder->get_result();
}
