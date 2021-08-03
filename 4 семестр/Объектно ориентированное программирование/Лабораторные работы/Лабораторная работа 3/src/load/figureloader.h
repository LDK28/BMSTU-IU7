#ifndef FIGURELOADER_H
#define FIGURELOADER_H

#include "builder.h"
#include "sourceloader.h"

class AbstractLoader
{
public:
    AbstractLoader() = default;
    virtual ~AbstractLoader() = default;

    virtual std::shared_ptr<Figure> load_figure(const std::string &file_name) = 0;
};

class FigureLoader : public AbstractLoader
{
public:
    FigureLoader() = default;
    FigureLoader(BaseBuilder &builder, SourceLoader &loader) { builder_ptr = std::shared_ptr<BaseBuilder>(&builder); src_loader_ptr = std::shared_ptr<SourceLoader>(&loader); };

    virtual std::shared_ptr<Figure> load_figure(const std::string &file_name) override;

    virtual ~FigureLoader() = default;

private:
    std::shared_ptr<BaseBuilder> builder_ptr;
    std::shared_ptr<SourceLoader> src_loader_ptr;
};

#endif // FIGURELOADER_H
