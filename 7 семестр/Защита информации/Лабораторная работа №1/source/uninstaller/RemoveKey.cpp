#include "uninstaller/RemoveKey.h"

void RemoveKey::removeKey()
{
    system("rm -rf ~/.config/security_application/ ");
    std::cout << "Uninstall success" << std::endl;
}