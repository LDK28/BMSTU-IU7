#include "application/Checker.h"
#include "application/Program.h"
#include <iostream>

int main()
{
    if (!Checker::checkSerial()) {
        std::cerr << "Application can't execute. Please contact your system administrator" << std::endl;
        return 1;
    }

    Program::execute();
    return 0;
}
