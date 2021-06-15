#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <cmath>
#include "clipping.h"

enum Mode { CLIP, FIGURE };
enum Error { NOT_CONVEX, CLIP_NOT_SET, FIGURE_NOT_SET, OK };

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void addFigureByButton(const QPoint &point);
    void addClipByButton(const QPoint &point);
    Error clipFigure();
    void setFigureColor(QColor &color);
    void setClipColor(QColor &color);
    void setClippedPartColor(QColor &color);
    void setClipMode();
    void setFigureMode();
    void clearAll();
    void clearFigure();
    void finishClip();
    void finishFigure();
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    Mode mode;
    QVector<QPoint> figure;
    QVector<QPoint> clip;
    QImage *image;
    int widget_height;
    int widget_width;
    QColor figure_color;
    QColor clip_color;
    QColor clipped_part_color;
    bool drawing_enabled;
    bool clip_set;
    bool figure_set;
    void redrawImage();
};

#endif // PAINTWIDGET_H
