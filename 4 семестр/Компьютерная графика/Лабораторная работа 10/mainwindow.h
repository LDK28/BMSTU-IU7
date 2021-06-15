#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
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

protected:
    void initializeFunctionComboBox();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_plotPushButton_clicked();
    void on_rotatePushButton_clicked();
    void on_selectFgColorPushButton_clicked();
    void on_selectBgColorPushButton_clicked();
    void on_clearAllPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap pixmap;
    bool plotted;
    void clearImage();
    void displayImage();

    double xb, xe, dx;
    double zb, ze, dz;
    double phi_x, phi_y, phi_z;
    void receiveFunctionRange();
    void receiveRotateAngles();
    void plot();

    QColor fgColor;
    QColor bgColor;
    QColor chooseColor(QColor initial, const QString &title);
    void setFgColor(QColor color);
    void setBgColor(QColor color);
    void setColor(QLabel *label, QColor &dst, QColor src);
    void colorLabel(QLabel *label, QColor color);
    void colorPixmap(QColor from, QColor to);

    bool zoom = false;  // experimental (doesn't work)
    int factor;
    void addZoom(int delta);
    void checkMaxZoom();
    void checkMinZoom();

    bool antialiasing = true;

    bool keyboard = true;
    bool w, a, s, d, plus, minus;
    void receiveKey(int key, bool value);

    bool mouse = true;
    QPoint drag;

private:
    static const QColor DEFAULT_FG_COLOR;
    static const QColor DEFAULT_BG_COLOR;
    static const int DEFAULT_ZOOM;
};

#endif // MAINWINDOW_H
