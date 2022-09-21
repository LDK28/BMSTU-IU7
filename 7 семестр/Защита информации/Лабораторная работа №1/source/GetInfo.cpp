#include "GetInfo.h"
    
std::string GetInfo::serial()
{
    char buffer[128];
    std::string result = "";

    FILE* pipe = popen("cat /etc/machine-id", "r");
    if (!pipe) {
        return "";
    }

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);

    result = result.substr(16);

    return result;
}

std::string GetInfo::pathToFile()
{
    char* path = getenv("HOME");
    strcat(path, "/.config/security_application/secret_key");
    return std::string(path);
}
