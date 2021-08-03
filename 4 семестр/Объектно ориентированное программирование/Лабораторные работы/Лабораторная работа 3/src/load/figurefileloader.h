#ifndef FIGUREFILELOADER_H
#define FIGUREFILELOADER_H

#include "basesourceloader.h"
#include "figurebuilder.h"

using namespace std;

class FigureFileLoader : public BaseSourceLoader
{
public:
    FigureFileLoader();
    FigureFileLoader(const shared_ptr<ifstream> &_stream);

    virtual void open(const string &file_name) override;
    virtual void close() override;

    virtual shared_ptr<Object> load() override;

private:
    shared_ptr<BaseFigureBuilder> builder;

private:
    vector<Point> read_points();
    vector<Edge> read_edges();
};

#endif // FIGUREFILELOADER_H
