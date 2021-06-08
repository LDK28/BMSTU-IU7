#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QVector>
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
    void on_addLinePushButton_clicked();
    void on_setClipperPushButton_clicked();
    void on_setLineBaseColorPushButton_clicked();
    void on_setClipperColorPushButton_clicked();
    void on_setClippedLineColorPushButton_clicked();
    void on_clipPushButton_clicked();
    void on_clearPushButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void receiveKeyboardModifiers(int &x, int &y);

private:
    Ui::MainWindow *ui;

    QPixmap pixmap;

    void clearImage();
    void displayImage();

    QColor lineBaseColor;
    QColor clipperColor;
    QColor clippedLineColor;
    void setLineBaseColor(const QColor &color);
    void setClipperColor(const QColor &color);
    void setClippedLineColor(const QColor &color);
    void colorLabel(const QColor &color, QLabel *label);

    QVector<QLine> lines;
    QRect clipper;
    bool left_clicked;
    bool right_clicked;
    void addLine(const QLine &line);
    void setClipper(const QRect &clipper);

    void clipLine(const QLine &line, int xl, int xr, int yb, int yt, QPainter &painter);
    int code(const QPoint &point, int xl, int xr, int yb, int yt);
};

#endif // MAINWINDOW_H
