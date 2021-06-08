#include "drawlabel.h"

DrawLabel::DrawLabel(QWidget *widget) : QLabel(widget) {}

void DrawLabel::setPixmapPointer(QPixmap &rpixmap)
{
    pixmap = &rpixmap;
}

void DrawLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pixmap);
    painter.end();
}
