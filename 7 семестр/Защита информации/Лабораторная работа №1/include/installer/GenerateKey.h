#ifndef __GENERATEKEY_H
#define __GENERATEKEY_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "GetInfo.h"

class GenerateKey
{
public:
    static int createFile();

private:
    static void makeDir();
    static int writeKey();
    static int error(int err);

    static const int SUCCESS;
    static const int OPEN_FILE_ERR;
    static const int COMMAND_ERR;
};

#endif // __GENERATEKEY_H
