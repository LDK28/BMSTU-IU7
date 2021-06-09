#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pixmap = QPixmap(ui->drawLabel->width(), ui->drawLabel->height());
    ui->drawLabel->setPixmapPointer(pixmap);

    on_clearAllPushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLinePushButton_clicked()
{
    const int x1 = ui->x1SpinBox->value();
    const int y1 = ui->y1SpinBox->value();
    const int x2 = ui->x2SpinBox->value();
    const int y2 = ui->y2SpinBox->value();

    addLine(QLine(x1, y1, x2, y2));
}

void MainWindow::on_addClipperVertexPushButton_clicked()
{
    const int x = ui->xSpinBox->value();
    const int y = ui->ySpinBox->value();

    if (closed)
        on_deleteClipperPushButton_clicked();

    clipper_vertices.push_back(QPoint(x, y));
    displayImage();
}

void MainWindow::on_setLineColorPushButton_clicked()
{
    setLineColor(QColorDialog::getColor(lineColor, this, "Pick a line's color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

void MainWindow::on_setClipperColorPushButton_clicked()
{
    setClipperColor(QColorDialog::getColor(clipperColor, this, "Pick a clipper's color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

void MainWindow::on_setClippedLineColorPushButton_clicked()
{
    setClippedLineColor(QColorDialog::getColor(clippedLineColor, this, "Pick a clipped line's color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

QVector<QLine> verticesToEdges(const QVector<QPoint>& vertices)
{
    QVector<QLine> edges;

    for (int i = 1; i < vertices.size(); ++i)
        edges.push_back(QLine(vertices[i - 1], vertices[i]));
    edges.push_back(QLine(vertices.back(), vertices.front()));

    return edges;
}

void MainWindow::on_clearAllPushButton_clicked()
{
    lines.clear();
    on_deleteClipperPushButton_clicked();

    setLineColor(Qt::red);
    setClipperColor(Qt::black);
    setClippedLineColor(Qt::blue);

    left_clicked = false;
}

void MainWindow::on_closeClipperPushButton_clicked()
{
    if (closed) {
        QMessageBox::critical(this, "Error", "Clipper already closed");
        return;
    }

    if (clipper_vertices.size() <= 2) {
        QMessageBox::critical(this, "Error", "Need at least 2 edges");
        return;
    }

    closed = true;
    displayImage();
}

void MainWindow::on_deleteClipperPushButton_clicked()
{
    clipper_vertices.clear();
    closed = false;
    displayImage();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x() - ui->drawLabel->x();
    int y = event->y() - ui->drawLabel->y();

    if (x < 0 || x >= ui->drawLabel->width() || y < 0 || y >= ui->drawLabel->height())
        return;

    switch (event->button()) {
    case Qt::LeftButton:
        if (left_clicked) {
            const int x1 = ui->x1SpinBox->value();
            const int y1 = ui->y1SpinBox->value();
            receiveKeyboardModifiers(x, y, x1, y1);
            ui->x2SpinBox->setValue(x);
            ui->y2SpinBox->setValue(y);
            on_addLinePushButton_clicked();
        }
        else {
            ui->x1SpinBox->setValue(x);
            ui->y1SpinBox->setValue(y);
            left_clicked = true;
        }
        break;
    case Qt::RightButton:
        if (!clipper_vertices.empty()) {
            const int x1 = ui->xSpinBox->value();
            const int y1 = ui->ySpinBox->value();
            receiveKeyboardModifiers(x, y, x1, y1);
        }
        ui->xSpinBox->setValue(x);
        ui->ySpinBox->setValue(y);
        on_addClipperVertexPushButton_clicked();
        break;
    default:
        break;
    }
}

void MainWindow::receiveKeyboardModifiers(int &x, int &y, int x1, int y1)
{
    switch (QApplication::keyboardModifiers()) {
    case Qt::ShiftModifier: {
        y = y1;
        break;
    }
    case Qt::ControlModifier: {
        x = x1;
        break;
    }
    case Qt::ShiftModifier | Qt::ControlModifier: {
        const int dx = x - x1;
        const int dy = y - y1;
        if (dx * dy >= 0) {
            const int d = (dx + dy) / 2;
            x = x1 + d;
            y = y1 + d;
        }
        else {
            const int d = (dx - dy) / 2;
            x = x1 + d;
            y = y1 - d;
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::displayImage()
{
    pixmap.fill();

    QPainter painter(&pixmap);

    painter.setPen(QPen(clipperColor, 3));
    for (int i = 1; i < clipper_vertices.size(); ++i)
        painter.drawLine(clipper_vertices[i - 1], clipper_vertices[i]);
    if (closed)
        painter.drawLine(clipper_vertices.back(), clipper_vertices.front());

    painter.setPen(lineColor);
    for (const auto &line: lines)
        painter.drawLine(line);

    ui->drawLabel->update();
}

void MainWindow::setLineColor(const QColor &color)
{
    lineColor = color;
    colorLabel(lineColor, ui->lineColorLabel);
}

void MainWindow::setClipperColor(const QColor &color)
{
    clipperColor = color;
    colorLabel(clipperColor, ui->clipperColorLabel);
}

void MainWindow::setClippedLineColor(const QColor &color)
{
    clippedLineColor = color;
    colorLabel(clippedLineColor, ui->clippedLineColorLabel);
}

void MainWindow::colorLabel(const QColor &color, QLabel *label) {
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), color);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}

void MainWindow::addLine(const QLine &line)
{
    lines.push_back(line);
    left_clicked = false;
    displayImage();
}

int sign(int x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

int product(const QPoint &a, const QPoint &b)
{
    return a.x() * b.y() - a.y() * b.x();
}

int direction(const QPoint &prev, const QPoint &curr, const QPoint &next)
{
    return sign(product(curr - prev, next - curr));
}

double product(const QPointF &a, const QPointF &b)
{
    return a.x() * b.x() + a.y() * b.y();
}

QPointF normvect(const QPointF &point)
{
    return {-point.y(), point.x()};
}

int checkConvex(const QVector<QPoint>& clipper_vertices)
{
    QPoint prev = clipper_vertices.back();
    QPoint curr = clipper_vertices[0];
    QPoint next = clipper_vertices[1];

    int prev_direction = direction(prev, curr, next);
    int first_direction = prev_direction;
    int curr_direction = 0;

    for (int i = 2; i <= clipper_vertices.size(); i++)
    {
        if (i == clipper_vertices.size())
        {
            prev = curr;
            curr = next;
            next = clipper_vertices[0];
        }
        else
        {
            prev = curr;
            curr = next;
            next = clipper_vertices[i];
            curr_direction = direction(prev, curr, next);
        }
        curr_direction = direction(prev, curr, next);
        if (curr_direction != prev_direction)
            return 0;

        prev_direction = curr_direction;
    }
    if (curr_direction != first_direction)
        return 0;
    return curr_direction;
}

void clipLine(const QLine &line, int direction, QVector<QLine> &edges, QPainter &painter)
{
    QPoint D = line.p2() - line.p1();
    float tb = 0;
    float te = 1;

    for (int i = 0; i < edges.size(); i++)
    {
        QPoint W = line.p1() - edges[i].p1();
        QPointF n = normvect(direction * (edges[i].p2() - edges[i].p1()));

        double d_scalar = product(D, n);
        double w_scalar = product(W, n);

        if (d_scalar == 0.0)
        {
            if (w_scalar < 0)
                return;
        }
        else
        {
            float t = -w_scalar / d_scalar;
            if (d_scalar > 0)
            {
                if (t > 1)
                    return;
                tb = qMax(tb, t);
            } else
            {
                if (t < 0)
                    return;
                te = qMin(te, t);
            }
        }
    }

    if (tb <= te)
        painter.drawLine(line.p1() + D * te, line.p1() + D * tb);
}

void MainWindow::on_clipPushButton_clicked()
{
    int direction = checkConvex(clipper_vertices);
    if (direction == 0)
    {
        QMessageBox::critical(nullptr, "Error", "Отсекатель должен быть выпуклым");
        return;
    }

    auto edges = verticesToEdges(clipper_vertices);

    QPainter painter(&pixmap);
    painter.setPen(QPen(clippedLineColor, 3));

    for (const auto &line: lines)
        clipLine(line, direction, edges, painter);

    ui->drawLabel->update();
}
