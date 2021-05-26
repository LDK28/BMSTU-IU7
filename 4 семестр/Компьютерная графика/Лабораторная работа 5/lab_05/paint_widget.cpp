#include "paint_widget.h"
#include <iostream>
Paint_widget::Paint_widget(int x, int y, int width, int height, QWidget *parent) : QWidget(parent)
{
    int widget_width = width;
    int widget_height = height;
    pen_color = Qt::black;
    brush_color = Qt::green;
    bg_color = QColor(255, 255, 255);
    delay = true;
    holes = 0;
    sleep_time = 15;

    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(bg_color);
    setGeometry(x, y, widget_width, widget_height);
}
void Paint_widget::redrawImage()
{
    image->fill(bg_color);
    QPainter painter(image);
    painter.setPen(pen_color);
    for (size_t i = 0; i < polygones.size(); i++)
    {
        draw_borders(&painter, polygones[i].edges);
    }
    update();
}
void Paint_widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event);
}
void Paint_widget::mousePressEvent(QMouseEvent *event)
{
    point p = {(int)(event->position().x()), (int)(event->position().y())};
    add_point(p);
}
void Paint_widget::finish_figure(std::vector <int> &time)
{
    if (polygones.empty())
        return;
    if (polygones.back().edges.empty())
    {
        holes--;
        polygones.pop_back();
    }
    else
        add_point(polygones.back().edges.front().p1);
    std::stack <edge_t> holes_stack;
    for (int i = 0; i < holes; i++)
    {
        for (size_t k = 0; k < polygones.back().edges.size(); k++)
        {
            holes_stack.push(polygones.back().edges[k]);
        }
        polygones.pop_back();
    }
    holes = 0;
    size_t stk_size = holes_stack.size();;
    for (size_t i = 0; i < stk_size; i++)
    {
        polygones.back().edges.push_back(holes_stack.top());
        holes_stack.pop();
    }

    polygones.back().finished = true;

    time.clear();
    int polygine_time;
    for (size_t i = 0; i < polygones.size(); i++)
    {
        list_flag_algo(polygones[i], polygine_time);
        time.push_back(polygine_time);
    }

    polygone_t polygone;
    polygones.push_back(polygone);
    polygones.back().finished = false;
}

void Paint_widget::add_hole()
{
    if (polygones.size() == 0)
        return;
    if (polygones.back().edges.empty())
        return;
    add_point(polygones.back().edges.front().p1);
    holes++;
    polygone_t polygone;
    polygones.push_back(polygone);
    polygones.back().finished = false;
}
void Paint_widget::add_point(point &p)
{
    if (polygones.empty())
    {
        polygone_t polygone;
        polygones.push_back(polygone);
        polygones.back().finished = false;
    }
    if (polygones.back().edges.empty())
    {
        edge_t edge;
        polygones.back().edges.push_back(edge);
        polygones.back().edges.back().p1 = p;
        polygones.back().edges.back().p2 = p;
        redrawImage();
        return;
    }
    if (polygones.back().edges.back().p1.x == polygones.back().edges.back().p2.x &&
         polygones.back().edges.back().p1.y == polygones.back().edges.back().p2.y)
    {
        polygones.back().edges.back().p2 = p;
        redrawImage();
        return;
    }
    edge_t edge = {polygones.back().edges.back().p2, p};
    polygones.back().edges.push_back(edge);
    redrawImage();
}
void Paint_widget::draw_borders(QPainter *painter, const std::vector <edge_t> &edges)
{
    if (painter == NULL)
        return;
    for (size_t i = 0; i < edges.size(); i++)
    {
        bresenham_int(painter, edges[i].p1, edges[i].p2);
    }
}
void Paint_widget::draw_point(QPainter *painter, int x, int y)
{
    if (painter == NULL)
        return;
    painter->drawPoint(x, y);
}
int Paint_widget::sign(double c)
{
    if (c < -1e-6)
        return -1;
    else
        return 1;
}
void Paint_widget::bresenham_int(QPainter *painter, const point &p_b, const point &p_e)
{
    if (p_b.x == p_e.x && p_b.y == p_e.y)
    {
        draw_point(painter, round(p_b.x), round(p_b.y));
        return;
    }
    point cur;
    int dx, dy;
    bool fl = 0;
    int sx, sy, f;
    dx = p_e.x - p_b.x;
    dy = p_e.y - p_b.y;
    sx = sign(dx);
    sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);
    if (dy >= dx)
    {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        fl = 1;
    }
    f = 2 * dy - dx;
    cur = p_b;
    int len = dx;
    for (int i = 0; i < len; i++)
    {
        draw_point(painter, cur.x, cur.y);
        if (f >= 0)
        {
            if (fl == 1)
                cur.x += sx;
            else
                cur.y += sy;
            f -= 2 * dx;
        }
        if (f < 0)
        {
            if (fl == 1)
                cur.y += sy;
            else
                cur.x += sx;
        }
        f += 2 * dy;
    }
}
void Paint_widget::find_figure_sizes(point &min, point &max, const std::vector <edge_t> &edges)
{
    min = edges[0].p1;
    max = edges[0].p1;
    for (size_t i = 0; i < edges.size(); i++)
    {
        if (edges[i].p1.x < min.x)
            min.x = edges[i].p1.x;
        if (edges[i].p1.x > max.x)
            max.x = edges[i].p1.x;

        if (edges[i].p1.y < min.y)
            min.y = edges[i].p1.y;
        if (edges[i].p1.y > max.y)
            max.y = edges[i].p1.y;

        if (edges[i].p2.x < min.x)
            min.x = edges[i].p2.x;
        if (edges[i].p2.x > max.x)
            max.x = edges[i].p2.x;

        if (edges[i].p2.y < min.y)
            min.y = edges[i].p2.y;
        if (edges[i].p2.y > max.y)
            max.y = edges[i].p2.y;
    }
}
void Paint_widget::bresenham_int_spec(QPainter &painter, QImage &image, const point &p_b, const point &p_e)
{
    if (p_b.x == p_e.x && p_b.y == p_e.y)
    {
        draw_point(&painter, p_b.x, p_b.y);
        return;
    }
    point cur;
    int dx, dy, dx_real, dy_real;
    bool fl = 0;
    int sx, sy, f;
    dx = p_e.x - p_b.x;
    dy = p_e.y - p_b.y;
    sx = sign(dx);
    sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);
    dx_real = dx;
    dy_real = dy;
    if (dy >= dx)
    {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        fl = 1;
    }
    f = 2 * dy - dx;
    cur = p_b;
    int len = dx + 1;
    int last_y = -1;
    for (int i = 0; i < len; i++)
    {
        // гарантируем, что последний пиксель линии, у которой dx > dy,
        // будет закрашен несмотря на заполнение по левой границе.
        // это нужно, чтобы в одной горизонтали не образовалось двух ограничивающих
        // пикселей, нарисованных разными линиями
        if (dx_real > dy_real && cur.y == p_e.y)
        {
            draw_point(&painter, p_e.x, p_e.y);
            break;
        }
        // заполняем по левой границе, чтобы обеспечить единственность ограничивающего пикселя
        // в одной строке
        if (cur.y != last_y)
        {
            last_y = cur.y;
            // точки не должны быть начальной и конечной, потому что иначе
            // на краях отрезка будут вставлены лишние пиксели, при этом обработкой
            // краёв занимается цикл по ребрам после отрисовки всего контура
            if (image.pixelColor(cur.x, cur.y) == painter.pen().color() && (cur.x != p_b.x || cur.y != p_b.y) && (cur.x != p_e.x || cur.y != p_e.y))
            {
                draw_point(&painter, cur.x + 1, cur.y);
            }
            else
            {
                draw_point(&painter, cur.x, cur.y);
            }
        }
        if (f >= 0)
        {
            if (fl == 1)
                cur.x += sx;
            else
                cur.y += sy;
            f -= 2 * dx;
        }
        if (f < 0)
        {
            if (fl == 1)
                cur.y += sy;
            else
                cur.x += sx;
        }
        f += 2 * dy;
    }
}
void Paint_widget::draw_outline(QColor &outline_color, QImage *outline_image, const std::vector <edge_t> &edges)
{
    QPainter painter(outline_image);
    painter.setPen(outline_color);
    // в результате будет нарисован контур, у которого в каждой горизонтали
    // чётное количество ограничивающих пикселей за исключением ситуаций
    // экстремумов
    for (size_t i = 0; i < edges.size(); i++)
    {
        bresenham_int_spec(painter, *outline_image, edges[i].p1, edges[i].p2);
    }
    // обработка экстремумов
   for (size_t i = 0; i < edges.size(); i++)
   {
       for (size_t j = 0; j < edges.size(); j++)
       {
           if (edges[i].p2.x == edges[j].p1.x && edges[i].p2.y == edges[j].p1.y)
           {
               if (sign(edges[i].p2.y - edges[i].p1.y) == sign(edges[j].p1.y - edges[j].p2.y))
                   draw_point(&painter, edges[i].p2.x + 1, edges[i].p2.y);
           }
       }
   }
}
void Paint_widget::invert_flag(bool &flag)
{
    if (flag)
        flag = false;
    else
        flag = true;
}
void Paint_widget::list_flag_algo(const polygone_t &polygone, int &time)
{
    struct timeval tv_start, tv_stop;
    time = 0;
    if (polygone.edges.empty())
        return;

    point min, max;
    find_figure_sizes(min, max, polygone.edges);

    // first step

    QImage outline_image(QSize(max.x + 5, max.y + 5), QImage::Format_RGBA64);
    outline_image.fill(QColor(50, 50, 50));
    if (!delay)
        gettimeofday(&tv_start, NULL);
    draw_outline(pen_color, &outline_image, polygone.edges);

    // second step

    if (polygone.finished == false)
        return;

    QPainter painter(image);
    painter.setPen(brush_color);

    bool flag = false;
    for (int y = min.y; y < max.y; y++)
    {
        flag = false;
        for (int x = min.x; x < max.x; x++)
        {
            if (outline_image.pixelColor(x, y) == pen_color)
                invert_flag(flag);
            if (flag)
                draw_point(&painter, x, y);

        }
        if (delay)
        {
            sleepFeature();
            update();
        }
    }
    if (!delay)
    {
        gettimeofday(&tv_stop, NULL);
        time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    painter.setPen(pen_color);
    draw_borders(&painter, polygone.edges);
    update();
}
void Paint_widget::sleepFeature()
{
    QTime end = QTime::currentTime().addMSecs(sleep_time);
    while (QTime::currentTime() < end)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
    return;
}
void Paint_widget::set_brush_color(const QColor &color)
{
    brush_color = color;
    redrawImage();
}
void Paint_widget::set_pen_color(const QColor &color)
{
    pen_color = color;
    redrawImage();
}
void Paint_widget::set_delay(bool delay, int time)
{
    this->delay = delay;
    if (delay)
        sleep_time = time;
}
void Paint_widget::erase()
{
    polygones.clear();
    redrawImage();
}
