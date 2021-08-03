#ifndef SCENEFILELOADER_H
#define SCENEFILELOADER_H


#include "figurefileloader.h"
#include "camerafileloader.h"
#include "scenebuilder.h"

using namespace std;

class BaseSceneLoader
{
public:
    BaseSceneLoader() = default;
    BaseSceneLoader(const shared_ptr<ifstream> &_stream);

    virtual void open(const string &file_name) = 0;
    virtual void close() = 0;

    virtual shared_ptr<Scene> load() = 0;
protected:
    shared_ptr<BaseSceneBuilder> builder;
    shared_ptr<ifstream> stream;

protected:
    Point read_point();
    Edge read_edge();
    int read_number();
};

class SceneFileLoader : public BaseSceneLoader
{
public:
    SceneFileLoader();
    SceneFileLoader(const shared_ptr<ifstream> &_stream);

    virtual void open(const string &file_name) override;
    virtual void close() override;

    virtual shared_ptr<Scene> load() override;

private:
    void read_objects(vector<shared_ptr<Object>> &objects, shared_ptr<BaseSourceLoader> &loader);
};

#endif // SCENEFILELOADER_H
