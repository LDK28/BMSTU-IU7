#include <QDebug>
#include "cabin.h"


Cabin::Cabin(QObject *parent) : QObject(parent)
{
    cross_floor_timer.setSingleShot(true);

    QObject::connect(&doors, SIGNAL(doors_closed()), this, SLOT(stay_closed()));
    QObject::connect(this, SIGNAL(cabin_stopped()), &doors, SLOT(opening()));
    QObject::connect(&cross_floor_timer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(move()));
}


void Cabin::move()
{
    if (state != START_MOVING && state != MOVE)
        return;

    if (state == MOVE)
        cur_floor += cur_direction;

    state = MOVE;
    emit cabin_crossed_floor(cur_floor, cur_direction);
    cross_floor_timer.start(CROSS_FLOOR_TIME);
}


void Cabin::stay_not_closed()
{
    if (state != MOVE && state != STAY_NOT_CLOSED)
        return;

    if (state == MOVE)
        qDebug() << "Stopped at floor " << cur_floor << ".";

    state = STAY_NOT_CLOSED;
    emit cabin_stopped();
}


void Cabin::stay_closed()
{
    if (state != STAY_NOT_CLOSED)
        return;

    state = STAY_CLOSED;
    qDebug() << "Lift is awaiting...";

    emit cabin_stay_closed(cur_floor);
}


void Cabin::start_moving(int floor, const direction &dir)
{
    UNUSED(floor);
    if (state != STAY_CLOSED)
        return;

    state = START_MOVING;
    cur_direction = dir;

    emit cabin_called();
}
