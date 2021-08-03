#ifndef CAMERAFILELOADER_H
#define CAMERAFILELOADER_H

#include "camerabuilder.h"
#include "basesourceloader.h"
#include "../exceptions/exceptions.h"
#include <chrono>

using namespace std;

class CameraFileLoader : public BaseSourceLoader
{
public:
    CameraFileLoader();
    CameraFileLoader(const shared_ptr<ifstream> &_stream);

    virtual void open(const string &file_name) override;
    virtual void close() override;

    virtual shared_ptr<Object> load() override;
private:
    shared_ptr<BaseCameraBuilder> builder;
};

#endif // CAMERAFILELOADER_H
