#include "viewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    viewer w;
    w.show();
    return a.exec();
}
