#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
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
    void on_addClipperVertexPushButton_clicked();
    void on_setLineColorPushButton_clicked();
    void on_setClipperColorPushButton_clicked();
    void on_setClippedLineColorPushButton_clicked();
    void on_clipPushButton_clicked();
    void on_clearAllPushButton_clicked();
    void on_closeClipperPushButton_clicked();
    void on_deleteClipperPushButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void receiveKeyboardModifiers(int &x, int &y, int x1, int y1);

private:
    Ui::MainWindow *ui;

    QPixmap pixmap;
    void displayImage();

    QColor lineColor;
    QColor clipperColor;
    QColor clippedLineColor;
    void setLineColor(const QColor &color);
    void setClipperColor(const QColor &color);
    void setClippedLineColor(const QColor &color);
    void colorLabel(const QColor &color, QLabel *label);

    QVector<QLine> lines;
    QVector<QPoint> clipper_vertices;
    bool left_clicked;
    bool closed;
    void addLine(const QLine &line);
};

#endif // MAINWINDOW_H
