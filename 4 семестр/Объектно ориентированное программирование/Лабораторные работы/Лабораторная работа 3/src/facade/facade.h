#ifndef FACADE_H
#define FACADE_H

#include "basecommand.h"
#include <memory>

using namespace std;

class Facade
{
public:
    void execute(shared_ptr<BaseCommand> command) {command->execute(); };
};

#endif // FACADE_H
