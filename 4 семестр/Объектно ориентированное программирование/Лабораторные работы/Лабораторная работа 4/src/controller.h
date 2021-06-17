#pragma once

#include <QObject>
#include <vector>
#include "consts.h"

using namespace std;


class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    void new_target(int floor);

public slots:
    void busy(int floor, const direction &_direction);
    void free(int floor);

signals:
    void cabin_achieved_target();
    void panel_new_target(int floor, const direction &_direction);

private:
    enum panel_state {
        FREE,
        BUSY
    };
    void next_target();
    panel_state state = FREE;
    int current_floor = 1;
    direction current_direction = STAY;
    vector<bool> is_target;

};
