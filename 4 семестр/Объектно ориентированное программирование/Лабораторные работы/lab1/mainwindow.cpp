#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <qpainter.h>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include <QColor>
#include <QColorDialog>
#include "io.h"
#include "controller.h"
#include "rc.h"
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene.scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene.scene);
    fig.n = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    QByteArray ba = path.toLocal8Bit();
    dataaction.filename = ba.data();

    rc_type rc = controller(scene,DOWNLOAD, dataaction);
    if (rc) print_warning(rc);
    rc = controller(scene, DRAW_NUMBER, dataaction);
    if (rc) print_warning(rc);
}

void MainWindow::on_pushButton_3_clicked()
{
    double km = ui->doubleSpinBox_6->value();
    dataaction.scale.k = km;
    rc_type rc = controller(scene, SCALE_NUMBER, dataaction);
    if (rc) print_warning(rc);
    rc = controller(scene, DRAW_NUMBER, dataaction);
    if (rc) print_warning(rc);
}

void MainWindow::on_pushButton_2_clicked()
{
    double dx = ui->doubleSpinBox_2->value();
    double dy = ui->doubleSpinBox_5->value();
    double dz = ui->doubleSpinBox_7->value();
    dataaction.move.dx = dx;
    dataaction.move.dy = dy;
    dataaction.move.dz = dz;

    rc_type rc = controller(scene, MOVE_NUMBER, dataaction);
    if (rc) print_warning(rc);
    rc = controller(scene, DRAW_NUMBER, dataaction);
    if (rc) print_warning(rc);
}

void MainWindow::on_pushButton_clicked()
{
    double ax = ui->doubleSpinBox->value();
    double ay = ui->doubleSpinBox_3->value();
    double az = ui->doubleSpinBox_4->value();
    dataaction.rotation.ax = ax;
    dataaction.rotation.ay = ay;
    dataaction.rotation.az = az;

    rc_type rc =controller(scene, ROTATION_NUMBER, dataaction);
    if (rc) print_warning(rc);
    rc = controller(scene, DRAW_NUMBER, dataaction);
    if (rc) print_warning(rc);
}

void MainWindow::on_pushButton_4_clicked()
{
    rc_type rc =controller(scene, DELETE_NUMBER, dataaction);
    if (rc) print_warning(rc);
    rc = controller(scene, DRAW_NUMBER, dataaction);
    if (rc) print_warning(rc);
}

