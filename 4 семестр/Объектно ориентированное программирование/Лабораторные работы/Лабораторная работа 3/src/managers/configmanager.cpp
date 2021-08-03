#include "configmanager.h"

ConfigManager::ConfigManager()
{
    shared_ptr<BaseRegistrator> registrator(new Registrator);
    registrator->registrate(solution);
}

shared_ptr<LoadCreator> ConfigManager::get_creator(int id)
{
    return solution.get_creator(id);
}

void ConfigManagerCreator::create_manager()
{
    static shared_ptr<ConfigManager>_manager(new ConfigManager);
    manager = _manager;
}

shared_ptr<ConfigManager> ConfigManagerCreator::get_manager()
{
    if (manager == nullptr)
        create_manager();

    return manager;
}
