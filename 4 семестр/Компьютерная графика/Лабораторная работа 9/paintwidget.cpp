#include "paintwidget.h"
#include <QtDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 1300;
    widget_height = 920;
    mode = CLIP;
    figure_color = Qt::black;
    clip_color = Qt::blue;
    clipped_part_color = Qt::red;
    drawing_enabled = false;
    clip_set = false;
    figure_set = false;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(Qt::white);
    setGeometry(20, 20, widget_width, widget_height);
    this->setMouseTracking(true);
}

void PaintWidget::redrawImage()
{
    image->fill(Qt::white);
    QPainter painter(image);
    if (clip_set || (mode == CLIP && drawing_enabled))
    {
        painter.setPen(clip_color);
        for (int i = 0; i < clip.size() - 1; i++)
        {
            painter.drawLine(clip[i], clip[i + 1]);
        }
        if (clip_set)
        {
            painter.drawLine(clip[0], clip.back());
        }
    }
    if (figure_set || (mode == FIGURE && drawing_enabled))
    {
        painter.setPen(figure_color);
        for (int i = 0; i < figure.size() - 1; i++)
        {
            painter.drawLine(figure[i], figure[i + 1]);
        }
        if (figure_set)
        {
            painter.drawLine(figure[0], figure.back());
        }
    }
    update();
}

void PaintWidget::finishClip()
{
    if (clip.size() >= 3)
    {
        clip_set = true;
        drawing_enabled = false;
        redrawImage();
    }
}

void PaintWidget::finishFigure()
{
    if (figure.size() >= 3)
    {
        figure_set = true;
        drawing_enabled = false;
        redrawImage();
    }
}

void PaintWidget::setFigureColor(QColor &color)
{
    figure_color.setRgb(color.rgb());
    redrawImage();
}

void PaintWidget::setClipColor(QColor &color)
{
    clip_color.setRgb(color.rgb());
    redrawImage();
}

void PaintWidget::setClippedPartColor(QColor &color)
{
    clipped_part_color.setRgb(color.rgb());
    redrawImage();
}

void PaintWidget::addFigureByButton(const QPoint &point)
{
    if (drawing_enabled)
    {
        figure.push_back(point);
        redrawImage();
    }
    else
    {
        if (figure_set)
        {
            figure_set = false;
            figure.clear();
        }
        QPainter painter(image);
        painter.setPen(figure_color);
        painter.drawPoint(point);
        drawing_enabled = true;
        figure.push_back(point);
        update();
    }
}

void PaintWidget::addClipByButton(const QPoint &point)
{
    if (drawing_enabled)
    {
        clip.push_back(point);
        redrawImage();
    }
    else
    {
        if (clip_set)
        {
            clip_set = false;
            clip.clear();
        }
        QPainter painter(image);
        painter.setPen(clip_color);
        painter.drawPoint(point);
        drawing_enabled = true;
        clip.push_back(point);
        update();
    }
}

Error PaintWidget::clipFigure()
{
    if (!clip_set) return CLIP_NOT_SET;
    if (!figure_set) return FIGURE_NOT_SET;
    if (drawing_enabled)
        drawing_enabled = false;
    QPainter painter(image);
    painter.setPen(QPen(clipped_part_color, 2));
    bool result = SutherlandHodgman(painter, clip, figure);
    update();
    if (result)
    {
        return OK;
    }
    return NOT_CONVEX;
}

void PaintWidget::clearAll()
{
    image->fill(Qt::white);
    if (figure_set || !figure.empty())
        figure.clear();
    figure_set = false;
    drawing_enabled = false;
    if (clip_set || !clip.empty())
        clip.clear();
    clip_set = false;
    update();
}

void PaintWidget::clearFigure()
{
    if (figure_set || !figure.empty())
        figure.clear();
    figure_set = false;
    drawing_enabled = false;
    redrawImage();
}

void PaintWidget::setFigureMode()
{
    mode = FIGURE;
    if (drawing_enabled)
    {
        drawing_enabled = false;
        if (!clip_set && !clip.empty())
        {
            clip.clear();
        }
        redrawImage();
    }
}

void PaintWidget::setClipMode()
{
    mode = CLIP;
    if (drawing_enabled)
    {
        drawing_enabled = false;
        if (!figure_set && !figure.empty())
        {
            figure.clear();
        }
        redrawImage();
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint cur_point = event->pos();
    if (drawing_enabled && mode == FIGURE)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (event->modifiers() == Qt::ShiftModifier)
            {
                if (abs(figure.back().x() - cur_point.x()) <= abs(figure.back().y() - cur_point.y()))
                {
                    cur_point.setX(figure.back().x());
                }
                else
                {
                    cur_point.setY(figure.back().y());
                }
            }
            figure.push_back(cur_point);
        }
        else if (event->button() == Qt::RightButton)
        {
            finishFigure();
        }
    }
    else if (drawing_enabled && mode == CLIP)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (event->modifiers() == Qt::ShiftModifier)
            {
                if (abs(clip.back().x() - cur_point.x()) <= abs(clip.back().y() - cur_point.y()))
                {
                    cur_point.setX(clip.back().x());
                }
                else
                {
                    cur_point.setY(clip.back().y());
                }
            }
            clip.push_back(cur_point);
        }
        else if (event->button() == Qt::RightButton)
        {
            finishClip();
        }
    }
    else
    {
        if (mode == CLIP)
        {
            clip_set = false;
            if (!clip.empty())
            {
                clip.clear();
            }
            clip.push_back(cur_point);
        }
        else if (mode == FIGURE)
        {
            figure_set = false;
            if (!figure.empty())
            {
                figure.clear();
            }
            figure.push_back(cur_point);
        }
        drawing_enabled = true;
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing_enabled)
    {
        redrawImage();
        QPainter painter(image);
        QPoint cur_point = event->pos();
        if (mode == FIGURE)
        {
            if (event->modifiers() == Qt::ShiftModifier)
            {
                if (abs(clip.back().x() - cur_point.x()) <= abs(clip.back().y() - cur_point.y()))
                {
                    cur_point.setX(clip.back().x());
                }
                else
                {
                    cur_point.setY(clip.back().y());
                }
            }

            painter.setPen(figure_color);
            painter.drawLine(figure.back(), cur_point);
        }
        else if (mode == CLIP)
        {
            if (event->modifiers() == Qt::ShiftModifier)
            {
                if (abs(clip.back().x() - cur_point.x()) <= abs(clip.back().y() - cur_point.y()))
                {
                    cur_point.setX(clip.back().x());
                }
                else
                {
                    cur_point.setY(clip.back().y());
                }
            }
            painter.setPen(clip_color);
            painter.drawLine(clip.back(), cur_point);
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event);
}

