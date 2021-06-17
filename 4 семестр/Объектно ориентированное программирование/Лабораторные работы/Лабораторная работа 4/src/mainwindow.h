#pragma once

#include <QMainWindow>
#include "lift.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_floor_01_clicked();
    void on_floor_02_clicked();
    void on_floor_03_clicked();
    void on_floor_04_clicked();
    void on_floor_05_clicked();
    void on_floor_06_clicked();
    void on_floor_07_clicked();
    void on_floor_08_clicked();
    void on_floor_09_clicked();
    void on_floor_10_clicked();

private:
    Ui::MainWindow *ui;
    Lift lift;
};
