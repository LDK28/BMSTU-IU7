#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QPainter>
#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <string.h>
#include <QPainter>
#include <QGraphicsScene>
#include "paint_widget.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class viewer; }
QT_END_NAMESPACE

class viewer : public QMainWindow
{
    Q_OBJECT

public:

    Paint_widget *paint_widget;

    viewer(QWidget *parent = nullptr);

    ~viewer();

    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_with_delay_but_clicked();

    void on_without_delay_but_clicked();

    void on_fill_but_clicked();

    void on_erase_but_clicked();

    void on_add_point_but_clicked();

    void on_add_hole_but_clicked();

    void on_delay_text_textChanged(const QString &arg1);

    void on_setPenColorButton_clicked();

    void on_setBrushColorButton_clicked();

private:
    Ui::viewer *ui;
};
#endif // VIEWER_H
