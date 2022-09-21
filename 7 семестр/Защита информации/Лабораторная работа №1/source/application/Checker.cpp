#include "application/Checker.h"

bool Checker::checkSerial()
{
    std::ifstream config;
    std::string path = GetInfo::pathToFile();
    config.open(path, std::ios::in | std::ios::binary);

    if (!config.is_open()) {
        return false;
    }

    std::string serial = GetInfo::serial();
    std::string buffer;
    config >> buffer;
    config.close();

    if (buffer + "\n" != serial) {
        return false;
    }

    return true;
}
