#ifndef SOURCELOADER_H
#define SOURCELOADER_H

#include <vector>
#include <fstream>
#include <string>

#include "point.h"
#include "edge.h"


class SourceLoader
{
public:
    SourceLoader() = default;

    virtual void open(const std::string &file_name) = 0;
    virtual void close() = 0;

    virtual Point load_center() = 0;
    virtual std::vector<Point> load_points() = 0;
    virtual std::vector<Edge> load_edges() = 0;

    ~SourceLoader() = default;
};

class FileLoader : public SourceLoader
{
public:
    FileLoader() = default;

    virtual void open(const std::string &file_name) override;
    virtual void close() override;

    virtual Point load_center() override;
    virtual std::vector<Point> load_points() override;
    virtual std::vector<Edge> load_edges() override;

    ~FileLoader() {if (is_open) close(); };

private:
    std::ifstream input_stream;
    bool is_open;
};

#endif // SOURCELOADER_H
