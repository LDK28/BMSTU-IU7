#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QLayout>
#include <cmath>
#include <QDebug>

const double EPS = sqrt(2);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pixmap = QPixmap(ui->drawLabel->width(), ui->drawLabel->height());
    ui->drawLabel->setPixmapPointer(pixmap);

    on_clearPushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLinePushButton_clicked()
{
    const int x1 = ui->x1addLineSpinBox->value();
    const int y1 = ui->y1addLineSpinBox->value();
    const int x2 = ui->x2addLineSpinBox->value();
    const int y2 = ui->y2addLineSpinBox->value();

    addLine(QLine(x1, y1, x2, y2));
}

void MainWindow::on_setClipperPushButton_clicked()
{
    int x1 = ui->x1setClipperSpinBox->value();
    int y1 = ui->y1setClipperSpinBox->value();
    int x2 = ui->x2setClipperSpinBox->value();
    int y2 = ui->y2setClipperSpinBox->value();

    if (x1 > x2)
        qSwap(x1, x2);

    if (y1 > y2)
        qSwap(y1, y2);


    setClipper(QRect(x1, y1, x2 - x1, y2 - y1));
}

void MainWindow::on_setLineBaseColorPushButton_clicked()
{
    setLineBaseColor(QColorDialog::getColor(lineBaseColor, this, "Pick a line base color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

void MainWindow::on_setClipperColorPushButton_clicked()
{
    setClipperColor(QColorDialog::getColor(clipperColor, this, "Pick a clipper color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

void MainWindow::on_setClippedLineColorPushButton_clicked()
{
    setClippedLineColor(QColorDialog::getColor(clippedLineColor, this, "Pick a clipped line color", QColorDialog::DontUseNativeDialog));
    displayImage();
}

void MainWindow::on_clipPushButton_clicked()
{
    QPainter painter(&pixmap);
    painter.setPen(QPen(clippedLineColor, 3));

    const int xl = clipper.x();
    const int xr = xl + clipper.width();
    const int yb = clipper.y();
    const int yt = yb + clipper.height();

    for (auto &line: lines)
        clipLine(line, xl, xr, yb, yt, painter);

    ui->drawLabel->update();
}

void MainWindow::on_clearPushButton_clicked()
{
    lines.clear();
    clipper = QRect(0, 0, 1, 1);
    displayImage();

    setLineBaseColor(Qt::green);
    setClipperColor(Qt::black);
    setClippedLineColor(Qt::red);

    left_clicked = false;
    right_clicked = false;
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
            receiveKeyboardModifiers(x, y);
            ui->x2addLineSpinBox->setValue(x);
            ui->y2addLineSpinBox->setValue(y);
            on_addLinePushButton_clicked();
        }
        else {
            ui->x1addLineSpinBox->setValue(x);
            ui->y1addLineSpinBox->setValue(y);
            left_clicked = true;
        }
        break;
    case Qt::RightButton:
        if (right_clicked) {
            ui->x2setClipperSpinBox->setValue(x);
            ui->y2setClipperSpinBox->setValue(y);
            on_setClipperPushButton_clicked();
        }
        else {
            ui->x1setClipperSpinBox->setValue(x);
            ui->y1setClipperSpinBox->setValue(y);
            right_clicked = true;
        }
    default:
        break;
    }
}

void MainWindow::receiveKeyboardModifiers(int &x, int &y)
{
    const int x1 = ui->x1addLineSpinBox->value();
    const int y1 = ui->y1addLineSpinBox->value();

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
    painter.drawRect(clipper);

    painter.setPen(lineBaseColor);
    for (auto const &line: lines)
        painter.drawLine(line);

    ui->drawLabel->update();
}

void MainWindow::setLineBaseColor(const QColor &color)
{
    lineBaseColor = color;
    colorLabel(lineBaseColor, ui->lineBaseColorLabel);
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

void MainWindow::setClipper(const QRect &clipper)
{
    this->clipper = clipper;
    right_clicked = false;
    displayImage();
}

void MainWindow::clipLine(const QLine &line, int xl, int xr, int yb, int yt, QPainter &p)
{
    QPoint P1 = line.p1();
    QPoint P2 = line.p2();
    int T1 = code(P1, xl, xr, yb, yt);
    int T2 = code(P2, xl, xr, yb, yt);
    int R1x = 0, R1y = 0;
    int R2x = 0, R2y = 0;
    int Xp, Yp;
    QPoint Q;
    int i;
    double m = pow(10, 30);
    if (!T1 && !T2)
    {
        p.drawLine(P1, P2);
        return;
    }
    if (T1 & T2)
    {
        return;
    }
    if (!T1)
    {
        R1x = P1.x();
        R1y = P1.y();
        Q = P2;
        i = 2;
        goto p15;
    }
    if (!T2)
    {
        R1x = P2.x();
        R1y = P2.y();
        Q = P1;
        i  = 2;
        goto p15;
    }
    i = 0;
    p12:
        i++;
    if (i > 2)
        goto p31;
    if (i == 1)
        Q = P1;
    else if (i == 2)
        Q = P2;
    p15:
        if (P1.x() == P2.x())
            goto p23;
    m = (double)(P2.y() - P1.y()) / (P2.x() - P1.x());
    if (Q.x() > xl)
        goto p20;
    Yp = m * (xl - Q.x()) + Q.y();
    if (Yp >= yb && Yp <= yt)
    {
        if (i == 1)
        {
            R1x = xl;
            R1y = Yp;
        }
        else if (i == 2)
        {
            R2x = xl;
            R2y = Yp;
        }
        goto p12;
    }
    p20:
        if (Q.x() < xr)
            goto p23;
    Yp = m * (xr - Q.x()) + Q.y();
    if (Yp >= yb && Yp <= yt)
    {
        if (i == 1)
        {
            R1x = xr;
            R1y = Yp;
            goto p12;
        }
        else if (i == 2)
        {
            R2x = xr;
            R2y = Yp;
            goto p12;
        }
    }
    p23:
        if (m == 0)
            goto p12;
    if (Q.y() < yt)
        goto p27;
    Xp = (yt - Q.y()) / m + Q.x();
    if (Xp >= xl && Xp <= xr)
    {
        if (i == 1)
        {
            R1x = Xp;
            R1y = yt;
        }
        else if (i == 2)
        {
            R2x = Xp;
            R2y = yt;
        }
        goto p12;
    }
    p27:
        if (Q.y() > yb)
            return;
    Xp = (yb - Q.y()) / m + Q.x();
    if (Xp >= xl && Xp <= xr)
    {
        if (i == 1)
        {
            R1x = Xp;
            R1y = yb;
        }
        else if (i == 2)
        {
            R2x = Xp;
            R2y = yb;
        }
        goto p12;
    }
    p31:
        p.drawLine(R1x, R1y, R2x, R2y);
}

int MainWindow::code(const QPoint& point, int xl, int xr, int yb, int yt)
{
    int res = 0;

    if (point.x() < xl)
        res |= 1;
    if (point.x() > xr)
        res |= 1 << 1;
    if (point.y() < yb)
        res |= 1 << 2;
    if (point.y() > yt)
        res |= 1 << 3;

    return res;
}
