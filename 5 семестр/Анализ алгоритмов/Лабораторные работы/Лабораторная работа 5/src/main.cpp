#include <iostream>
#include <thread>

#include "conveyor.h"

using namespace std;

int main() 
{
    setbuf(stdout, NULL);
    
    Conveyor *conveyor_obj = new Conveyor();
    cout << endl << "Linear running:" << endl;
    conveyor_obj->run_linear(50);

    // need to make a log for parallel
    
    // cout << endl << "Parallel running:" << endl;
    // conveyor_obj->run_parallel(50);

    delete conveyor_obj;

    return 0;
}
