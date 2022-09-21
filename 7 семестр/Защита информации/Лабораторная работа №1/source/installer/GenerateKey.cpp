#include "installer/GenerateKey.h"

const int GenerateKey::SUCCESS = 0;
const int GenerateKey::OPEN_FILE_ERR = 1;
const int GenerateKey::COMMAND_ERR = 2;

int GenerateKey::createFile()
{
    makeDir();
    return error(writeKey());
}

void GenerateKey::makeDir()
{
    system("mkdir -p ~/.config/security_application");
}

int GenerateKey::writeKey()
{
    std::string serial = GetInfo::serial();
    if (serial == "")
    {
        return COMMAND_ERR;
    }

    std::string path = GetInfo::pathToFile();
    std::ofstream config;

    config.open(path, std::ios::out | std::ios::binary);
    if (!config.is_open())
    {
        return OPEN_FILE_ERR;
    }

    config << serial;

    config.close();
    return SUCCESS;
}

int GenerateKey::error(int err)
{
    switch (err)
    {
    case SUCCESS:
        std::cout << "Installation success" << std::endl;
        break;

    case OPEN_FILE_ERR:
        std::cerr << "Error while open file" << std::endl;
        break;

    case COMMAND_ERR:
        std::cerr << "Error while take serial" << std::endl;
        break;
    }

    return err;
}
