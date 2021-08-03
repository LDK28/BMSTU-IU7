#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "basemanager.h"
#include "configuration/registrator.h"
#include "configuration/solution.h"

class ConfigManager
{
public:
    ConfigManager();
    ~ConfigManager() = default;

    shared_ptr<LoadCreator> get_creator(int id);

private:
    Solution solution;
};

class ConfigManagerCreator
{
public:
    ConfigManagerCreator() = default;
    ~ConfigManagerCreator() = default;

    std::shared_ptr<ConfigManager> get_manager();
private:
    void create_manager();

    std::shared_ptr<ConfigManager> manager;
};


#endif // CONFIGMANAGER_H
