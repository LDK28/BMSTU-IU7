#ifndef CREATOR_H
#define CREATOR_H

#include <memory>

class Creator
{
public:
    Creator() = default;

    virtual std::shared_ptr<Controller> get_product() = 0;

protected:
    virtual std::shared_ptr<Controller> create_product() = 0;
};

class FigureLoaderCreator : public Creator
{
    static bool created;
public:
    FigureLoaderCreator() =default;

    virtual std::shared_ptr<Controller> get_product() override;
protected:
    virtual std::shared_ptr<Controller> create_product() override;
};

#endif // CREATOR_H
