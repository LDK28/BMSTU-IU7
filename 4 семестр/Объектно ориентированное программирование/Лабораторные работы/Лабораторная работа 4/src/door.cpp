#include <QDebug>
#include "door.h"


Door::Door(QObject *parent) : QObject(parent)
{
    doors_stay_timer.setInterval(STAY_TIME);

    doors_stay_timer.setSingleShot(true);
    doors_open_timer.setSingleShot(true);
    doors_close_timer.setSingleShot(true);

    QObject::connect(&doors_open_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&doors_close_timer, SIGNAL(timeout()), this, SLOT(closed()));
    QObject::connect(&doors_stay_timer, SIGNAL(timeout()), this, SLOT(closing()));
    QObject::connect(this, SIGNAL(doors_opened()), &doors_stay_timer, SLOT(start()));
}


void Door::opening()
{
    if (state != CLOSING && state != CLOSED)
        return;

    qDebug() << "Doors are opening...";
    if (state == CLOSED)
    {
        state = OPENING;
        doors_open_timer.start(DOORS_TIME);
    }
    else
    {
        state = OPENING;
        int t = doors_close_timer.remainingTime();
        doors_close_timer.stop();
        doors_open_timer.start(DOORS_TIME - t);
    }
}


void Door::closing()
{
    if (state != OPENED)
        return;

    state = CLOSING;
    qDebug() << "Doors are closing...";
    doors_close_timer.start(DOORS_TIME);

    // киндер сюрприз
//    else if (current_state == CLOSED)
//    {
//        emit closed_doors();
//    }
    //
}


void Door::opened()
{
    if (state != OPENING)
        return;

    state = OPENED;
    qDebug() << "The doors are opened!\nWaiting for passengers...";

    emit doors_opened();
}


void Door::closed()
{
    if (state != CLOSING)
        return;

    state = CLOSED;
    qDebug() << "The doors are closed!";

    emit doors_closed();
}
