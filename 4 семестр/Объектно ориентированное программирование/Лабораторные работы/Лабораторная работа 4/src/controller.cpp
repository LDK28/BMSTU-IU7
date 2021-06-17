#include <QDebug>
#include "controller.h"
#include "consts.h"


Controller::Controller(QObject *parent) : QObject(parent)
{
    for (size_t i = 0; i < FLOORS; i++)
        is_target.push_back(false);

    QObject::connect(this, SIGNAL(panel_new_target(int, direction)), this, SLOT(busy(int, direction)));
}


void Controller::new_target(int floor)
{
    is_target[floor - 1] = true;
    next_target();
}


void Controller::next_target()
{
    if (is_target[current_floor - 1])
    {
        emit panel_new_target(current_floor, STAY);
    }
    else if (state == FREE)
    {
        for (int i = 0; i < static_cast<int>(is_target.size()); i++)
            if (is_target[i])
            {
                if (i + 1 > current_floor)
                    emit panel_new_target(i + 1, UP);
                else
                    emit panel_new_target(i + 1, DOWN);
                break;
            }
    }
}


void Controller::busy(int floor, const direction &_direction)
{
    if (state == FREE)
    {
        state = BUSY;
        current_direction = _direction;
    }
    else if (state == BUSY)
    {
        current_floor = floor;
        if (is_target[floor - 1])
        {
            is_target[floor - 1] = false;
            emit cabin_achieved_target();
        }
        else
            qDebug() << "Moving... floor:" << floor;
    }
}


void Controller::free(int floor)
{
    state = FREE;
    current_floor = floor;
    next_target();
}
