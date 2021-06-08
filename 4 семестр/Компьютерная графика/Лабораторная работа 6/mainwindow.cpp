#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    closed(false),
    EdgeColor(Qt::black),
    FillColor(Qt::black),
    fillColor(FillColor),
    pixmap(1401, 721),
    image(1401, 721, QImage::Format_RGB32),
    start_point(0)
{
    ui->setupUi(this);

    ui->drawLabel->setPixmapPointer(pixmap);

    clearImage();
    colorLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();

    if (x < 0 || y < 0)
        return;

    if (event->button() == Qt::RightButton) {
        ui->x0SpinBox->setValue(x);
        ui->y0SpinBox->setValue(y);
        return;
    }

    addPoint(QPoint(x, y), drawType());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();

    if (x < 0 || y < 0)
        return;

    addPoint(QPoint(x, y), drawType());
}

void MainWindow::on_addPointPushButton_clicked()
{
    const int x = ui->xSpinBox->text().toInt();
    const int y = ui->ySpinBox->text().toInt();
    addPoint(QPoint(x, y), DrawType::none);
}

void MainWindow::on_closePushButton_clicked()
{
    if (closed) {
        QMessageBox::critical(this, "Error", "Already closed");
        return;
    }

    if (start_point + 2 >= points.size()) {
        QMessageBox::critical(this, "Error", "Need at least 2 edges");
        return;
    }

    addEdge(QLine(points[points.size() - 1], points[start_point]));
    closed = true;
}

void MainWindow::on_fillPushButton_clicked()
{
    if (!closed) {
//        QMessageBox::critical(this, "Error", "Close figure!");
//        return;
        on_closePushButton_clicked();
    }

    const int delay_value = ui->delaySpinBox->value();

    QPainter painter(&pixmap);
    QPoint pix; // Затравочный пиксель
    painter.setPen(fillColor);
    QStack<QPoint> stack;
    stack.push(QPoint(ui->x0SpinBox->value(), ui->y0SpinBox->value()));
    while (!stack.empty())
    {
        pix = stack.pop();
        painter.drawPoint(pix);

        int x = pix.x();
        int y = pix.y();

        for (x = pix.x() + 1; x <= x_max && !edgePixel(x, y); x++)
            painter.drawPoint(x, y);
        int xr = x - 1;

        for (x = pix.x() - 1; x >= x_min && !edgePixel(x, y); x--)
            painter.drawPoint(x, y);
        int xl = x + 1;

        pushNewPixel(stack, y + 1, xl, xr);
        pushNewPixel(stack, y - 1, xl, xr);

        if (ui->delayCheckBox->isChecked())
        {
            displayImage();
            delay(delay_value);
        }
        else
            image = pixmap.toImage();
    }

    displayImage();
}

bool MainWindow::edgePixel(int x, int y)
{
    return image.pixelColor(x, y) == EdgeColor;
}

bool MainWindow::cleanPixel(int x, int y)
{
    const QColor color = image.pixelColor(x, y);
    return color != EdgeColor && color != fillColor;
}

void MainWindow::pushNewPixel(QStack<QPoint> &stack, int y, int xl, int xr)
{
    if (y < y_min || y > y_max)
        return;

    for (int x = xl; x <= xr;)
    {
        bool flag = false;
        for (; x <= xr && cleanPixel(x, y); x++)
            flag = true;
        if (flag)
        {
            if (x == xr && cleanPixel(x, y))
                stack.push(QPoint(x, y));
            else
                stack.push(QPoint(x - 1, y));

        }

        flag = false;
        for (; x < xr && !cleanPixel(x, y); x++)
            flag = true;
        if (!flag)
            x++;
    }
}

void MainWindow::on_clearPushButton_clicked()
{
    clearImage();
    closed = false;
    points.clear();
    edges.clear();
    start_point = 0;
    ui->tableWidget->clearContents();
    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());
}

void MainWindow::on_setColorPushButton_clicked()
{
    fillColor = QColorDialog::getColor(fillColor, this, "Pick a color", QColorDialog::DontUseNativeDialog);
    if (fillColor == EdgeColor)
        fillColor = QColor(2, 2, 2);
    colorLabel();
}

typename MainWindow::DrawType MainWindow::drawType()
{
    DrawType drawType = DrawType::none;
    switch (QApplication::keyboardModifiers()) {
    case Qt::ShiftModifier:
        drawType = DrawType::horizontal;
        break;
    case Qt::ControlModifier:
        drawType = DrawType::vertical;
        break;
    case Qt::ShiftModifier | Qt::ControlModifier:
        drawType = DrawType::diagonal;
        break;
    default:
        break;
    }

    return drawType;
}

void MainWindow::addPoint(const QPoint &point, DrawType drawType)
{
    const int n = points.size();
    points.push_back(point);
    ui->tableWidget->insertRow(n);

    if (n && !closed)
        switch (drawType) {
        case DrawType::horizontal:
            points[n].setY(points[n - 1].y());
            break;
        case DrawType::vertical:
            points[n].setX(points[n - 1].x());
            break;
        case DrawType::diagonal: {
            const int dx = points[n].x() - points[n - 1].x();
            const int dy = points[n].y() - points[n - 1].y();
            if (dx * dy >= 0) {
                const int d = (dx + dy) / 2;
                points[n].setX(points[n - 1].x() + d);
                points[n].setY(points[n - 1].y() + d);
            }
            else {
                const int d = (dx - dy) / 2;
                points[n].setX(points[n - 1].x() + d);
                points[n].setY(points[n - 1].y() - d);
            }
        }
        case DrawType::none:
        default:
            break;
        }

    ui->tableWidget->setItem(n, 0, new QTableWidgetItem(QString::number(points[n].x())));
    ui->tableWidget->setItem(n, 1, new QTableWidgetItem(QString::number(points[n].y())));

    if (closed) {
        start_point = n;
        closed = false;
    }
    else if (n)
        addEdge(QLine(points[closed ? 0 : n - 1], points[n]));
}

void MainWindow::addEdge(const QLine &edge)
{
    edges.push_back(edge);

    QPainter painter(&pixmap);
    painter.drawLine(edge);
    displayImage();
}

void MainWindow::delay(int times)
{
    for (int i = 0; i < times; i++) {
        repaint();
        resize(width(), height());
    }
}

void MainWindow::clearImage()
{
    pixmap.fill();
    displayImage();
}

void MainWindow::displayImage()
{
    ui->drawLabel->update();
    image = pixmap.toImage();
}

void MainWindow::colorLabel()
{
    QPalette palette = ui->colorLabel->palette();
    palette.setColor(ui->colorLabel->backgroundRole(), fillColor);
    ui->colorLabel->setAutoFillBackground(true);
    ui->colorLabel->setPalette(palette);
}
