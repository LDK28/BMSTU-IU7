#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paint_widget = new PaintWidget(this);

    enable_add = false;

    QRegExp check("[-+]?\\d+$");
    QRegExpValidator *valid = new QRegExpValidator(check, this);

    ui->addButton->setEnabled(false);

    ui->lineEditX->setValidator(valid);
    ui->lineEditY->setValidator(valid);

    connect(ui->lineEditX, SIGNAL(textChanged(QString)), this, SLOT(addEnabled()));
    connect(ui->lineEditY, SIGNAL(textChanged(QString)), this, SLOT(addEnabled()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEnabled()
{

    enable_add = ui->lineEditX->hasAcceptableInput() &&
            ui->lineEditY->hasAcceptableInput();
    ui->addButton->setEnabled(enable_add);

}

void MainWindow::on_clipRadioButton_clicked()
{
    paint_widget->setClipMode();
}

void MainWindow::on_figureRadioButton_clicked()
{
    paint_widget->setFigureMode();
}

void MainWindow::on_chooseFigureColorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (color.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, color);
        ui->figureFrame->setPalette(palette);
        paint_widget->setFigureColor(color);
    }
}

void MainWindow::on_chooseClipColorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (color.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, color);
        ui->clipFrame->setPalette(palette);
        paint_widget->setClipColor(color);
    }
}

void MainWindow::on_chooseClippedPartButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (color.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, color);
        ui->clippedPartFrame->setPalette(palette);
        paint_widget->setClippedPartColor(color);
    }
}

void MainWindow::on_clearAllButton_clicked()
{
    paint_widget->clearAll();
}

void MainWindow::on_addButton_clicked()
{
    QString tmp;
    int x, y;
    tmp = ui->lineEditX->text();
    x = tmp.toInt();
    tmp = ui->lineEditY->text();
    y = tmp.toInt();
    if (ui->clipRadioButton->isChecked())
    {
        paint_widget->addClipByButton(QPoint(x, y));
    }
    else if (ui->figureRadioButton->isChecked())
    {
        paint_widget->addFigureByButton(QPoint(x, y));
    }
}

void MainWindow::on_clipButton_clicked()
{
    Error rc = paint_widget->clipFigure();
    if (rc == NOT_CONVEX)
    {
        QMessageBox::warning(this, "Ошибка", "Отсекатель не выпуклый");
    }
    else if (rc == CLIP_NOT_SET)
    {
        QMessageBox::warning(this, "Ошибка", "Отсекатель не задан");
    }
    else if (rc == FIGURE_NOT_SET)
    {
        QMessageBox::warning(this, "Ошибка", "Многоугольник не задан");
    }
}

void MainWindow::on_clearFigureButton_clicked()
{
    paint_widget->clearFigure();
}

void MainWindow::on_finishButton_clicked()
{
    if (ui->figureRadioButton->isChecked())
    {
        paint_widget->finishFigure();
    }
    else if (ui->clipRadioButton->isChecked())
    {
        paint_widget->finishClip();
    }
}
