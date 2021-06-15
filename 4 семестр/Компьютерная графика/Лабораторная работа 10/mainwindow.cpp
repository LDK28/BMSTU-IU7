#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBitmap>
#include <QColorDialog>
#include <QMessageBox>
#include "algorithm.h"
#include "functions.h"
#include "global.h"

const QColor MainWindow::DEFAULT_FG_COLOR = Qt::black;
const QColor MainWindow::DEFAULT_BG_COLOR = Qt::white;
const int MainWindow::DEFAULT_ZOOM = 50;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeFunctionComboBox();

    pixmap = QPixmap(ui->drawLabel->width(), ui->drawLabel->height());
    ui->drawLabel->setPixmapPointer(pixmap);

    on_clearAllPushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeFunctionComboBox()
{
    for (auto&& function: FUNCTIONS)
        ui->functionComboBox->addItem(function.name);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!mouse || !plotted || event->button() != Qt::LeftButton)
        return;

    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();

    if (x < 0 || y < 0 || x > 720 || y > 720)
        return;

    drag = {x, y};
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!mouse || !plotted || event->buttons() != Qt::LeftButton)
        return;

    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();

    if (x < 0 || y < 0 || x > 720 || y > 720)
        return;

    phi_x += drag.y() - y;
    phi_y += drag.x() - x;

    plot();

    drag = {x, y};
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (!zoom || !mouse || !plotted)
        return;

    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();

    if (x < 0 || y < 0 || x > 720 || y > 720)
        return;

    addZoom(event->delta() / 8);

    plot();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!keyboard || !plotted)
        return;

    receiveKey(event->key(), true);

    static const double delta_phi = 5;
    static const int delta_zoom = 1;

    if (w)
        phi_x += delta_phi;
    if (a)
        phi_y += delta_phi;
    if (s)
        phi_x -= delta_phi;
    if (d)
        phi_y -= delta_phi;

    if (zoom) {
        if (plus)
            addZoom(delta_zoom);
        if (minus)
            addZoom(-delta_zoom);
    }

    plot();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!keyboard)
        return;

    receiveKey(event->key(), false);
}

void MainWindow::on_plotPushButton_clicked()
{
    receiveFunctionRange();
    phi_x = phi_y = phi_z = 0;

    plot();
    plotted = true;
}

void MainWindow::on_rotatePushButton_clicked()
{
    if (!plotted) {
        QMessageBox::warning(this, "Warning", "First you need plot function");
        return;
    }

    receiveFunctionRange();
    receiveRotateAngles();

    plot();
}

void MainWindow::on_selectFgColorPushButton_clicked()
{
    setFgColor(chooseColor(fgColor, "Select foreground color"));
}

void MainWindow::on_selectBgColorPushButton_clicked()
{
    setBgColor(chooseColor(bgColor, "Select background color"));
}

void MainWindow::on_clearAllPushButton_clicked()
{
    plotted = false;

    setColor(ui->fgColorLabel, fgColor, DEFAULT_FG_COLOR);
    setColor(ui->bgColorLabel, bgColor, DEFAULT_BG_COLOR);

    clearImage();

    factor = DEFAULT_ZOOM;
//	checkMaxZoom();

    w = a = s = d = plus = minus = false;

    ui->drawLabel->update();
}

void MainWindow::clearImage()
{
    pixmap.fill(bgColor);
}

void MainWindow::displayImage()
{
    ui->drawLabel->update();
}

void MainWindow::receiveFunctionRange()
{
    xb = ui->xbDoubleSpinBox->value();
    xe = ui->xeDoubleSpinBox->value();
    dx = ui->dxDoubleSpinBox->value();

    zb = ui->zbDoubleSpinBox->value();
    ze = ui->zeDoubleSpinBox->value();
    dz = ui->dzDoubleSpinBox->value();
}

void MainWindow::receiveRotateAngles()
{
    phi_x += ui->phixDoubleSpinBox->value();
    phi_y += ui->phiyDoubleSpinBox->value();
    phi_z += ui->phizDoubleSpinBox->value();
}

void MainWindow::plot()
{
    const Function& func = FUNCTIONS[ui->functionComboBox->currentIndex()];
    const FunctionData data = {
        xb, xe, dx,
        zb, ze, dz,
        phi_x, phi_y, phi_z
    };

    checkMaxZoom();

    clearImage();

    QPainter painter(&pixmap);
    painter.setPen(fgColor);

    if (antialiasing)
        painter.setRenderHint(QPainter::Antialiasing, true);

    FloatingHorizonAlgorithm(painter, func, data, factor);

    displayImage();
}

QColor MainWindow::chooseColor(QColor initial, const QString &title)
{
    return QColorDialog::getColor(initial, this, title, QColorDialog::DontUseNativeDialog);
}

void MainWindow::setFgColor(QColor color)
{
    // TODO: check color

    setColor(ui->fgColorLabel, fgColor, color);
}

void MainWindow::setBgColor(QColor color)
{
    setColor(ui->bgColorLabel, bgColor, color);
}

void MainWindow::setColor(QLabel *label, QColor &dst, QColor src)
{
    const QColor __dst = dst;

    dst = src;
    colorLabel(label, src);

    if (plotted) {
        if (antialiasing)
            plot();
        else
            colorPixmap(__dst, src);
    }
}

void MainWindow::colorLabel(QLabel *label, QColor color)
{
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), color);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}

void MainWindow::colorPixmap(QColor from, QColor to)
{
    auto mask = pixmap.createMaskFromColor(from, Qt::MaskOutColor);

    QPainter painter(&pixmap);
    painter.setPen(to);

    painter.drawPixmap(pixmap.rect(), mask, mask.rect());

    displayImage();
}

void MainWindow::addZoom(int delta)
{
    factor += delta;

    checkMaxZoom();
    checkMinZoom();
}

void MainWindow::checkMaxZoom()
{
    if (int max_factor = 720 / 2 / 3 / max(qAbs(xe), qAbs(xb), qAbs(ze), qAbs(zb)); factor >= max_factor)
        factor = max_factor;
}

void MainWindow::checkMinZoom()
{
    if (int min_factor = 1; factor <= min_factor)
        factor = min_factor;
}

void MainWindow::receiveKey(int key, bool value)
{
    switch (key) {
    case Qt::Key_W:
//	case Qt::Key_Up:
        w = value;
        break;
    case Qt::Key_A:
//	case Qt::Key_Left:
        a = value;
        break;
    case Qt::Key_S:
//	case Qt::Key_Down:
        s = value;
        break;
    case Qt::Key_D:
//	case Qt::Key_Right:
        d = value;
        break;
    case Qt::Key_Plus:
        plus = value;
        break;
    case Qt::Key_Minus:
        minus = value;
        [[fallthrough]]
    default:
        break;
    }
}
