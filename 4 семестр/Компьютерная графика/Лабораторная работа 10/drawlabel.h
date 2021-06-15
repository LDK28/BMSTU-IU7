#ifndef DRAWLABEL_H
#define DRAWLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>

class DrawLabel : public QLabel
{
    Q_OBJECT

public:
    DrawLabel(QWidget *widget);
    void setPixmapPointer(QPixmap &rpixmap);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap *pixmap;
};

#endif // DRAWLABEL_H
