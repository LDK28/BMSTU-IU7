#pragma once

#include <QObject>
#include "controller.h"
#include "cabin.h"


class Lift : public QObject
{
    Q_OBJECT
public:
    explicit Lift(QObject *parent = nullptr);

signals:

public slots:
    void call(int floor);

private:
    Controller controller;
    Cabin cabin;
};
