#include "mainwindow.h"
#include "./ui_mainwindow.h"

void drawAxes(QGraphicsScene *scene)
{
    scene->addLine(0, 0, 1000, 0, QPen(Qt::lightGray));
    scene->addLine(0, 0, 0, 550, QPen(Qt::lightGray));

    QGraphicsTextItem *text;
    for (int i = 0; i <= 1000; i += 100)
    {
        text = scene->addText(QString::number(i));
        text->setPos(i - 20, -25);
        scene->addLine(i, 3, i, -3, QPen(Qt::lightGray));
    }
    for (int i = 50; i <= 550; i += 50)
    {
        text = scene->addText(QString::number(i));
        text->setPos(-40, i - 15);
        scene->addLine(3, i, -3, i, QPen(Qt::lightGray));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    color = new QPen;

    color->setColor(Qt::black);

    ui->lineEdit->setValidator(new QDoubleValidator(this));
    ui->lineEdit_2->setValidator(new QDoubleValidator(this));
    ui->lineEdit_3->setValidator(new QDoubleValidator(this));
    ui->lineEdit_4->setValidator(new QDoubleValidator(this));
    ui->lineEdit_5->setValidator(new QDoubleValidator(this));
    ui->lineEdit_6->setValidator(new QDoubleValidator(this));
    ui->lineEdit_7->setValidator(new QDoubleValidator(this));
    ui->lineEdit_8->setValidator(new QDoubleValidator(this));
    ui->lineEdit_9->setValidator(new QDoubleValidator(this));
    ui->lineEdit_10->setValidator(new QDoubleValidator(this));

    ui->radioButton->setChecked(1);
    ui->radioButton_6->setChecked(1);
    ui->lineEdit_4->setDisabled(1);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0, 0, 1000, 550);

    drawAxes(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    double x, y, r1, r2;
    QString value;

    value = ui->lineEdit->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    x = value.toDouble();

    value = ui->lineEdit_2->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    y = value.toDouble();

    value = ui->lineEdit_3->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r1 = value.toDouble();

    if (ui->radioButton_7->isChecked())
    {
        value = ui->lineEdit_4->text();
        if (value.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Пропущено поле");
            return;
        }
        r2 = value.toDouble();
    }
    else
        r2 = r1;

    if (ui->radioButton->isChecked())
    {
        if (ui->radioButton_6->isChecked())
            canonicalCircle(scene, *color, x, y, r1);
        else
            canonicalEllips(scene, *color, x, y, r1, r2);
    }
    if (ui->radioButton_2->isChecked())
    {
        if (ui->radioButton_6->isChecked())
            parametricCircle(scene, *color, x, y, r1);
        else
            parametricEllips(scene, *color, x, y, r1, r2);
    }
    if (ui->radioButton_3->isChecked())
    {
        if (ui->radioButton_6->isChecked())
            bresenhamCircle(scene, *color, x, y, r1);
        else
            bresenhamEllips(scene, *color, x, y, r1, r2);
    }
    if (ui->radioButton_4->isChecked())
    {
        if (ui->radioButton_6->isChecked())
            midPointCircle(scene, *color, x, y, r1);
        else
            midPointEllips(scene, *color, x, y, r1, r2);
    }
    if (ui->radioButton_5->isChecked())
    {
        scene->addEllipse(x - r1, y - r2, r1 * 2, r2 * 2, *color);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    scene->clear();
    drawAxes(scene);
}

void MainWindow::on_radioButton_6_clicked()
{
    ui->lineEdit_4->setDisabled(1);
}


void MainWindow::on_radioButton_7_clicked()
{
    ui->lineEdit_4->setEnabled(1);
}

void MainWindow::on_pushButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
        *color = newColor;
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
        ui->graphicsView->setBackgroundBrush(newColor);

}

void MainWindow::on_pushButton_5_clicked()
{
    double x, y, r1, r2, step;
    long count;
    QString value;

    value = ui->lineEdit_5->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    x = value.toDouble();

    value = ui->lineEdit_6->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    y = value.toDouble();

    value = ui->lineEdit_7->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r1 = value.toDouble();

    value = ui->lineEdit_8->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r2 = value.toDouble();

    value = ui->lineEdit_9->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    step = value.toDouble();

    value = ui->lineEdit_10->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    count = value.toInt();

    if (ui->radioButton_6->isChecked())
    {
        long i = 0;
        for (double r = r1; r <= r2 && i <= count; r += step)
        {
            if (ui->radioButton->isChecked())
            {
                canonicalCircle(scene, *color, x, y, r);
            }
            if (ui->radioButton_2->isChecked())
            {
                parametricCircle(scene, *color, x, y, r);
            }
            if (ui->radioButton_3->isChecked())
            {
                bresenhamCircle(scene, *color, x, y, r);
            }
            if (ui->radioButton_4->isChecked())
            {
                midPointCircle(scene, *color, x, y, r);
            }
            if (ui->radioButton_5->isChecked())
            {
                scene->addEllipse(x - r, y - r, r * 2, r * 2, *color);
            }
            ++i;
        }
    }
    else
    {
        double step2 = r2 / r1 * step;
        for (long i = 0; i < count; ++i)
        {
            if (ui->radioButton->isChecked())
            {
                canonicalEllips(scene, *color, x, y, r1, r2);
            }
            if (ui->radioButton_2->isChecked())
            {
                parametricEllips(scene, *color, x, y, r1, r2);
            }
            if (ui->radioButton_3->isChecked())
            {
                bresenhamEllips(scene, *color, x, y, r1, r2);
            }
            if (ui->radioButton_4->isChecked())
            {
                midPointEllips(scene, *color, x, y, r1, r2);
            }
            if (ui->radioButton_5->isChecked())
            {
                scene->addEllipse(x - r1, y - r2, r1 * 2, r2 * 2, *color);
            }
            r1 += step;
            r2 += step2;
        }
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    QLayout *layout = new QVBoxLayout();
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *plot = new QGraphicsScene;
    layout->addWidget(view);
    view->setScene(plot);
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    plot->setSceneRect(0, 0, 800, 500);


    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    widget->show();
}
