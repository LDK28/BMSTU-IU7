#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDoubleValidator>
#include <QGraphicsTextItem>
#include <QFont>
#include <QColorDialog>
#include <QMessageBox>
#include <string>
#include <circle.h>
#include <ellips.h>
#include <ctime>
#include <fstream>

using namespace std;

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
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButto3_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_radioButton6_clicked();

    void on_radioButton7_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPen *color;
};
#endif // MAINWINDOW_H
