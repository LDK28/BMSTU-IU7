#include "camerabuilder.h"

std::shared_ptr<Object> CameraBuilder::get_result()
{
    return std::shared_ptr<Object>(new Camera(position, direction));
}
