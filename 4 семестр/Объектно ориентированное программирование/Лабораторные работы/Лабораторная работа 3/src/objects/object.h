#ifndef OBJECT_H
#define OBJECT_H

#include "point.h"
#include "../Mathobj/mathobjs.h"

class Visitor;

#include <memory>
#include <vector>

using namespace std;

class Object;

using VectorObject = vector<shared_ptr<Object>>;
using IteratorObject = VectorObject::const_iterator;

class Object
{
public:
    Object() = default;
    ~Object() = default;

    virtual bool is_composite() {return false; };
    virtual bool add(shared_ptr<Object> &) {return false; };
    virtual bool remove(const IteratorObject &) {return false; };
    virtual IteratorObject begin() {return IteratorObject(); };
    virtual IteratorObject end() {return IteratorObject(); };


    virtual void conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate) = 0;
    virtual void accept(Visitor &visitor) = 0;
};

class InvisibleObject : public Object
{
public:
    InvisibleObject() = default;
    ~InvisibleObject() = default;

    virtual bool is_visible() const {return false; };
};

class VisibleObject : public Object
{
public:
    VisibleObject() = default;
    ~VisibleObject() = default;

    virtual bool is_visible() const {return true; };
};

#endif // OBJECT_H
