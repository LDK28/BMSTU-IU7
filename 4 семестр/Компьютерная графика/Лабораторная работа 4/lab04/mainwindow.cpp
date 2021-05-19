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

    ui->lineEdit1->setValidator(new QDoubleValidator(this));
    ui->lineEdit2->setValidator(new QDoubleValidator(this));
    ui->lineEdit3->setValidator(new QDoubleValidator(this));
    ui->lineEdit4->setValidator(new QDoubleValidator(this));
    ui->lineEdit5->setValidator(new QDoubleValidator(this));
    ui->lineEdit6->setValidator(new QDoubleValidator(this));
    ui->lineEdit7->setValidator(new QDoubleValidator(this));
    ui->lineEdit8->setValidator(new QDoubleValidator(this));
    ui->lineEdit9->setValidator(new QDoubleValidator(this));
    ui->lineEdit10->setValidator(new QDoubleValidator(this));

    ui->radioButton1->setChecked(1);
    ui->radioButton6->setChecked(1);
    ui->lineEdit4->setDisabled(1);

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


void MainWindow::on_radioButton6_clicked()
{
    ui->lineEdit4->setDisabled(1);
}


void MainWindow::on_radioButton7_clicked()
{
    ui->lineEdit4->setEnabled(1);
}


void MainWindow::on_pushButton1_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
        *color = newColor;
}


void MainWindow::on_pushButton2_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid())
        ui->graphicsView->setBackgroundBrush(newColor);
}


void MainWindow::on_pushButto3_clicked()
{
    double x, y, r1, r2;
    QString value;

    value = ui->lineEdit1->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    x = value.toDouble();

    value = ui->lineEdit2->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    y = value.toDouble();

    value = ui->lineEdit3->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r1 = value.toDouble();

    if (ui->radioButton7->isChecked())
    {
        value = ui->lineEdit4->text();
        if (value.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Пропущено поле");
            return;
        }
        r2 = value.toDouble();
    }
    else
        r2 = r1;

    if (ui->radioButton1->isChecked())
    {
        if (ui->radioButton6->isChecked())
            canonicalCircle(scene, *color, x, y, r1, 1);
        else
            canonicalEllips(scene, *color, x, y, r1, r2, 1);
    }
    if (ui->radioButton2->isChecked())
    {
        if (ui->radioButton6->isChecked())
            parametricCircle(scene, *color, x, y, r1, 1);
        else
            parametricEllips(scene, *color, x, y, r1, r2, 1);
    }
    if (ui->radioButton3->isChecked())
    {
        if (ui->radioButton6->isChecked())
            bresenhamCircle(scene, *color, x, y, r1, 1);
        else
            bresenhamEllips(scene, *color, x, y, r1, r2, 1);
    }
    if (ui->radioButton4->isChecked())
    {
        if (ui->radioButton6->isChecked())
            midPointCircle(scene, *color, x, y, r1, 1);
        else
            midPointEllips(scene, *color, x, y, r1, r2, 1);
    }
    if (ui->radioButton5->isChecked())
    {
        scene->addEllipse(x - r1, y - r2, r1 * 2, r2 * 2, *color);
    }
}


void MainWindow::on_pushButton4_clicked()
{
    scene->clear();
    drawAxes(scene);
}


void MainWindow::on_pushButton5_clicked()
{
    double x, y, r1, r2, step;
    long count;
    QString value;

    value = ui->lineEdit5->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    x = value.toDouble();

    value = ui->lineEdit6->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    y = value.toDouble();

    value = ui->lineEdit7->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r1 = value.toDouble();

    value = ui->lineEdit8->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    r2 = value.toDouble();

    value = ui->lineEdit9->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    step = value.toDouble();

    value = ui->lineEdit10->text();
    if (value.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пропущено поле");
        return;
    }
    count = value.toInt();

    if (ui->radioButton6->isChecked())
    {
        long i = 0;
        for (double r = r1; r <= r2 && i <= count; r += step)
        {
            if (ui->radioButton1->isChecked())
            {
                canonicalCircle(scene, *color, x, y, r, 1);
            }
            if (ui->radioButton2->isChecked())
            {
                parametricCircle(scene, *color, x, y, r, 1);
            }
            if (ui->radioButton3->isChecked())
            {
                bresenhamCircle(scene, *color, x, y, r, 1);
            }
            if (ui->radioButton4->isChecked())
            {
                midPointCircle(scene, *color, x, y, r, 1);
            }
            if (ui->radioButton5->isChecked())
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
            if (ui->radioButton1->isChecked())
            {
                canonicalEllips(scene, *color, x, y, r1, r2, 1);
            }
            if (ui->radioButton2->isChecked())
            {
                parametricEllips(scene, *color, x, y, r1, r2, 1);
            }
            if (ui->radioButton3->isChecked())
            {
                bresenhamEllips(scene, *color, x, y, r1, r2, 1);
            }
            if (ui->radioButton4->isChecked())
            {
                midPointEllips(scene, *color, x, y, r1, r2, 1);
            }
            if (ui->radioButton5->isChecked())
            {
                scene->addEllipse(x - r1, y - r2, r1 * 2, r2 * 2, *color);
            }
            r1 += step;
            r2 += step2;
        }
    }
}


void MainWindow::on_pushButton6_clicked()
{
    ofstream outfile ("../lab04/data.txt");

    double startRadius = 5000;
    double secondRadius = 1000;
    double endRadius = 50000;
    double step = 5000;
    double x = 500;
    double y = 350;
    color->setColor(Qt::white);
    size_t count = 1000;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();

    for (long radius = startRadius; radius <= endRadius; radius += step)
        outfile << radius << endl;
    outfile << endl;

    if (ui->radioButton6->isChecked())
    {
        outfile << "Сравнение методов построения окружности" << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();
                canonicalCircle(scene, *color, x, y, radius, 0);
                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();
                parametricCircle(scene, *color, x, y, radius, 0);
                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();
                bresenhamCircle(scene, *color, x, y, radius, 0);
                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();
                midPointCircle(scene, *color, x, y, radius, 0);
                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();
                scene->addEllipse(x - radius, y - radius, radius * 2, radius * 2, *color);
                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::microseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
        }
        outfile << endl;
    }
    else
    {
        outfile << "Сравнение методов построения эллипса" << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();

                canonicalEllips(scene, *color, x, y, radius, secondRadius, 0);

                end = chrono::high_resolution_clock::now();
                sum += chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
            secondRadius += step;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();

                parametricEllips(scene, *color, x, y, radius, secondRadius, 0);

                end = chrono::high_resolution_clock::now();
                sum += chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
            secondRadius += step;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();

                bresenhamEllips(scene, *color, x, y, radius, secondRadius, 0);

                end = chrono::high_resolution_clock::now();

                sum += chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
            secondRadius += step;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();

                midPointEllips(scene, *color, x, y, radius, secondRadius, 0);

                end = chrono::high_resolution_clock::now();
                sum += chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
            secondRadius += step;
        }
        outfile << endl;

        for (long radius = startRadius; radius <= endRadius; radius += step)
        {
            size_t sum = 0;
            for (size_t i = 0; i < count; ++i)
            {
                start = chrono::high_resolution_clock::now();

                scene->addEllipse(x - radius, y - radius, radius * 2, secondRadius * 2, *color);

                end = chrono::high_resolution_clock::now();
                sum += chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            sum /= count;
            outfile << sum << endl;
            secondRadius += step;
        }
        outfile << endl;
    }


    outfile.close();

    system("/Users/vladimirprocenko/pythonProject/bin/python3.9 ../lab04/plot.py");
}

