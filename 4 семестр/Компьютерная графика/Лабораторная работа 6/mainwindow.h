#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QStack>
#include <QColorDialog>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void on_addPointPushButton_clicked();
    void on_closePushButton_clicked();
    void on_fillPushButton_clicked();
    void on_clearPushButton_clicked();
    void on_setColorPushButton_clicked();

private:
    Ui::MainWindow *ui;

    bool closed;
    QVector<QPoint> points;
    QVector<QLine> edges;

    const QColor EdgeColor = Qt::black;
    const QColor FillColor;
    QColor fillColor;
    QPixmap pixmap;
    QImage image;

    int start_point;
    enum DrawType {	none, horizontal, vertical, diagonal };
    DrawType drawType();
    void addPoint(const QPoint &point, DrawType drawType);
    void addEdge(const QLine &edge);

    void delay(int);
    void clearImage();
    void displayImage();
    void colorLabel();

    static const int x_min = 0;
    static const int y_min = 0;
    static const int x_max = 1400;
    static const int y_max = 720;
    void pushNewPixel(QStack<QPoint> &stack, int y, int xl, int xr);
    bool cleanPixel(int x, int y);
    bool edgePixel(int x, int y);
};
#endif // MAINWINDOW_H
