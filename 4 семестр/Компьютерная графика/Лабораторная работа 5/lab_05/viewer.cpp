#include "viewer.h"
#include "ui_viewer.h"
#include <iostream>

viewer::viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::viewer)
{
    ui->setupUi(this);
    ui->delay_text->setValidator(new QIntValidator(this));
    ui->x_text->setValidator(new QDoubleValidator(this));
    ui->y_text->setValidator(new QDoubleValidator(this));
    paint_widget = new Paint_widget(300,
                                    0,
                                    this->geometry().width(),
                                    this->geometry().height(), this);

    ui->current_pen_color->setStyleSheet(QString("background-color: black"));
    ui->current_brush_color->setStyleSheet(QString("background-color: %1").arg(QColor (Qt::green).name()));

}

viewer::~viewer()
{
    delete ui;
}
void viewer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        std::vector <int> time;
        paint_widget->finish_figure(time);
    }
    if (event->key() == Qt::Key_Shift)
    {
        paint_widget->add_hole();
    }

}

void viewer::on_add_point_but_clicked()
{
    bool ok;
    int x = ui->x_text->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка", "Некорректное координата X");
        return;
    }
    int y = ui->y_text->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка", "Некорректное координата Y");
        return;
    }
    point p = {x, y};
    paint_widget->add_point(p);
}
void viewer::on_add_hole_but_clicked()
{
    paint_widget->add_hole();
}
void viewer::on_fill_but_clicked()
{
    std::vector <int> time;
    paint_widget->finish_figure(time);
}
void viewer::on_erase_but_clicked()
{
    paint_widget->erase();
}

void viewer::on_with_delay_but_clicked()
{
    bool ok;
    int time = ui->delay_text->text().toInt(&ok);
    if (!ok)
        return;
    paint_widget->set_delay(true, time);
    ui->delay_text->setEnabled(1);
}

void viewer::on_without_delay_but_clicked()
{
    paint_widget->set_delay(false);
    ui->delay_text->setEnabled(0);
}

void viewer::on_delay_text_textChanged(const QString &arg1)
{
    int time;
    if (ui->with_delay_but->isChecked())
    {
        bool ok;
        time = arg1.toInt(&ok);
        if (!ok)
            return;
        paint_widget->set_delay(true, time);
    }
}

void viewer::on_setPenColorButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
    {
        paint_widget->set_pen_color(newColor);
        ui->current_pen_color->setStyleSheet(QString("background-color: %1").arg(newColor.name()));
    }
}

void viewer::on_setBrushColorButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
    {
        paint_widget->set_brush_color(newColor);
        ui->current_brush_color->setStyleSheet(QString("background-color: %1").arg(newColor.name()));
    }
}

