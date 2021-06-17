#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Stopped at 1 floor, doors are closed.\n"
                "Waiting state...";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_floor_01_clicked()
{
    qDebug() << "Cabin pressed button 1.";
    lift.call(1);
}

void MainWindow::on_floor_02_clicked()
{
    qDebug() << "Cabin pressed button 2.";
    lift.call(2);
}


void MainWindow::on_floor_03_clicked()
{
    qDebug() << "Cabin pressed button 3.";
    lift.call(3);
}


void MainWindow::on_floor_04_clicked()
{
    qDebug() << "Cabin pressed button 4.";
    lift.call(4);
}


void MainWindow::on_floor_05_clicked()
{
    qDebug() << "Cabin pressed button 5.";
    lift.call(5);
}


void MainWindow::on_floor_06_clicked()
{
    qDebug() << "Cabin pressed button 6.";
    lift.call(6);
}


void MainWindow::on_floor_07_clicked()
{
    qDebug() << "Cabin pressed button 7.";
    lift.call(7);
}


void MainWindow::on_floor_08_clicked()
{
    qDebug() << "Cabin pressed button 8.";
    lift.call(8);
}


void MainWindow::on_floor_09_clicked()
{
    qDebug() << "Cabin pressed button 9.";
    lift.call(9);
}


void MainWindow::on_floor_10_clicked()
{
    qDebug() << "Cabin pressed button 10.";
    lift.call(10);
}
