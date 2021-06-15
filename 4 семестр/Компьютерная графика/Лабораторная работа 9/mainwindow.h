#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>
#include <QColorDialog>
#include <QMessageBox>
#include "paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addEnabled();
    void on_clipRadioButton_clicked();
    void on_figureRadioButton_clicked();
    void on_chooseFigureColorButton_clicked();
    void on_chooseClipColorButton_clicked();
    void on_chooseClippedPartButton_clicked();
    void on_clearAllButton_clicked();
    void on_addButton_clicked();
    void on_clipButton_clicked();
    void on_clearFigureButton_clicked();
    void on_finishButton_clicked();

private:
    PaintWidget *paint_widget;
    Ui::MainWindow *ui;
    bool enable_add;
};

#endif // MAINWINDOW_H
