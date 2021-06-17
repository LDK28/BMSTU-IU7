#include "lift.h"


Lift::Lift(QObject *parent) : QObject(parent)
{
    QObject::connect(&controller, SIGNAL(panel_new_target(int,direction)), &cabin, SLOT(start_moving(int, direction)));
    QObject::connect(&cabin, SIGNAL(cabin_crossed_floor(int,direction)), &controller, SLOT(busy(int, direction)));
    QObject::connect(&controller, SIGNAL(cabin_achieved_target()), &cabin, SLOT(stay_not_closed()));
    QObject::connect(&cabin, SIGNAL(cabin_stay_closed(int)), &controller, SLOT(free(int)));
}

void Lift::call(int floor)
{
    controller.new_target(floor);
}
