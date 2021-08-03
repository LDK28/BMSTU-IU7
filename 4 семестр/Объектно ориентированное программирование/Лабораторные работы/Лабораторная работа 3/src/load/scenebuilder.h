#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "../scene/scene.h"
#include "builder.h"

class BaseSceneBuilder : public Builder
{
public:
    BaseSceneBuilder() = default;
    ~BaseSceneBuilder() = default;

    virtual bool is_build() = 0;
    virtual void reset() = 0;
    virtual void build_objects(std::vector<shared_ptr<Object>> &objects) = 0;
    virtual std::shared_ptr<Scene> get_result() = 0;
protected:
    std::shared_ptr<Scene> scene;
};

class SceneBuilder : public BaseSceneBuilder
{
public:
    SceneBuilder() = default;
    ~SceneBuilder() = default;

    virtual bool is_build() override {return scene != nullptr; };
    virtual void reset() override {scene = shared_ptr<Scene>(new Scene); };
    virtual void build_objects(std::vector<shared_ptr<Object>> &objects) override;
    virtual std::shared_ptr<Scene> get_result() override;
};

#endif // SCENEBUILDER_H
