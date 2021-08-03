#ifndef SCENE_H
#define SCENE_H

#include "../objects/object.h"
#include "../objects/composite.h"

using namespace std;

class Scene
{
public:
    Scene() :objects(new Composite), camera_set(false) {};
    ~Scene() = default;

    void accept(Visitor &visitor);
    void conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate);

    void add_object(shared_ptr<Object> &obj) {objects->add(obj); };
    void remove_object(int index) {objects->remove(objects->begin() + index); };
    void remove_object(IteratorObject &it) {objects->remove(it);};

    shared_ptr<Object> get_objects() const {return objects; };

    IteratorObject begin() {return objects->begin(); }
    IteratorObject end() {return objects->end(); }


    Scene &operator=(const Scene &scene) {objects = scene.objects; return (*this); };

private:
    shared_ptr<Object> objects;
    bool camera_set;
};

#endif // SCENE_H
