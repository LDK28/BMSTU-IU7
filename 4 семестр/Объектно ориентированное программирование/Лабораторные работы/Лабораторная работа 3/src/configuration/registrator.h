#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include "load/loadcreator.h"
#include "solution.h"
#include <fstream>

class BaseRegistrator
{
public:
    BaseRegistrator() = default;
    ~BaseRegistrator() = default;

    virtual void registrate(Solution &solution) = 0;
};


class Registrator : public BaseRegistrator
{
public:
    Registrator() = default;
    ~Registrator() = default;

    virtual void registrate(Solution &solution) override;
};

#endif // REGISTRATOR_H
