#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <QString>

using FunctionOfTwoVariables = std::function<double(double, double)>;

struct Function
{
    QString name;
    FunctionOfTwoVariables function;

    double operator()(double x, double z) const {
        return function(x, z);
    }
};

struct FunctionData
{
    double xb, xe, dx;
    double zb, ze, dz;
    double phi_x, phi_y, phi_z;
};

#endif // FUNCTION_H
