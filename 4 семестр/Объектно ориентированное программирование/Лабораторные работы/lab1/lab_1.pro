QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab_1
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    io.cpp \
    functions.cpp \
    controller.cpp \
    rc.cpp \
    myscene.cpp \
    figure.cpp \
    points.cpp \
    action.cpp \
    matrix.cpp \
    tools.cpp

HEADERS += \
        mainwindow.h \
    io.h \
    functions.h \
    controller.h \
    rc.h \
    myscene.h \
    figure.h \
    points.h \
    action.h \
    matrix.h \
    tools.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    3.txt \
    2.txt \
    1.txt \
    4.txt \
    cube.txt
