#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H

#include "builder.h"

class BaseFigureBuilder
{
public:
    BaseFigureBuilder() = default;
    ~BaseFigureBuilder() = default;

    virtual bool is_build() = 0;

    virtual void build_center(Point &center) = 0;
    virtual void build_points(vector<Point> &points) = 0;
    virtual void build_edges(vector<Edge> &edges) = 0;
    virtual void reset() = 0;

    virtual shared_ptr<Object> get_result() = 0;
protected:
    Data data;
    bool is_center, is_points, is_edges;
};

class FigureBuilder : public BaseFigureBuilder
{
public:
    FigureBuilder() = default;

    virtual bool is_build() override {return is_center && is_points && is_edges; };

    virtual void build_center(Point &center) override;
    virtual void build_points(vector<Point> &points) override;
    virtual void build_edges(vector<Edge> &edges) override;
    virtual void reset() override {is_center = is_points = is_edges = false; };

    virtual shared_ptr<Object> get_result() override;
    ~FigureBuilder() = default;
};

#endif // FIGUREBUILDER_H
