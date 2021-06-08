QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab06
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    drawlabel.cpp

HEADERS += \
        mainwindow.h \
    drawlabel.h

FORMS += \
        mainwindow.ui
