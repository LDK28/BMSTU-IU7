#include "functions.h"

const QVector<Function> FUNCTIONS = {
    {"|cos(x) * sin(x)|", [](double x, double z) {
            return std::abs(std::cos(x) * std::sin(z));
    }},

    {"exp(cos(x) * sin(z))", [](double x, double z) {
        return std::exp(std::cos(x) * std::sin(z));
    }},

    {"1 - ", [](double x, double z) {
        return sqrt(1 - (x * x) + z * z);
    }},

    {"exp(|sin(x + z) * cos(x + z)|)", [](double x, double z) {
        return std::exp(std::abs(0.5 * std::sin(2.0 * (x + z))));
    }}
};
