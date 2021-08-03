#ifndef BUILDER_H
#define BUILDER_H

#include <memory>
#include "../objects/figure.h"

using namespace std;

class Builder
{
public:
    Builder() = default;
    ~Builder() = default;

    virtual bool is_build() = 0;
    virtual void reset() = 0;
};



#endif // BUILDER_H
