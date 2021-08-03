#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <memory>
#include "../objects/object.h"
#include "../objects/edge.h"
#include <chrono>
#include "../exceptions/exceptions.h"

#include <fstream>

using namespace std;


class BaseSourceLoader
{
public:
    BaseSourceLoader() = default;
    ~BaseSourceLoader() = default;

    virtual void open(const string &file_name) = 0;
    virtual void close() = 0;

    virtual shared_ptr<Object> load() = 0;
protected:
    std::shared_ptr<ifstream> stream;

protected:
    Point read_point();
    Edge read_edge();
    int read_number();
};

#endif // LOADER_H
