#include "registrator.h"

void Registrator::registrate(Solution &solution)
{
    solution.registrate(0, shared_ptr<LoadCreator>(new FigureLoadCreator));
    solution.registrate(1, shared_ptr<LoadCreator>(new CameraLoadCreator));
}
