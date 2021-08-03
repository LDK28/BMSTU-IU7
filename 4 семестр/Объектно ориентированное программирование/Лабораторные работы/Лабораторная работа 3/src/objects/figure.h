#ifndef FIGURE_H
#define FIGURE_H

class Visitor;

#include "object.h"
#include <vector>
#include "point.h"
#include "../Mathobj/mathobjs.h"
#include "edge.h"
#include "../exceptions/exceptions.h"
#include "data.h"
#include <chrono>
#include "visitor/visitor.h"

using namespace std;

class Figure : public VisibleObject
{
public:
    Figure() = default;
    Figure(const Data &_data) {data = _data; };

    virtual void conversion(const Point &transfer, const ScaleCoef &scale, const Angle &rotate) override;
    virtual void accept(Visitor &visitor) override;

    friend class Visitor;

    ~Figure() {data.clear(); };
private:
    void transfer(const Point &transfer);
    void rotate(const Angle &angle);
    void scale(const ScaleCoef &scale);

protected:
    Data data;
    const Data &get_data() const {return data; };
};

#endif // FIGURE_H
