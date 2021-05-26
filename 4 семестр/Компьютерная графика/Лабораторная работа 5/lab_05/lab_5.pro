QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab_5
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        paint_widget.cpp \
        viewer.cpp


HEADERS += \
        paint_widget.h \
        viewer.h

FORMS += \
    viewer.ui

DISTFILES += \
