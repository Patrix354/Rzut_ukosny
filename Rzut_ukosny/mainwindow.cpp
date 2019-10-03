#include "mainwindow.h"
#include "ui_mainwindow.h"

#define g 9.80665

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    angle = 0;
    dt = 0;
    V = 0;
    Xn = 0;
    Yn = 0;
    Vx = 0;
    Vy = 0;

    ui->Graph->addGraph();
    ui->Graph->xAxis->setLabel("x");
    ui->Graph->yAxis->setLabel("y");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    angle = ui->angle_edit->text().toInt(nullptr, 10);
    dt = ui->dt_edit->text().toDouble(nullptr);
    V = ui->V_edit->text().toDouble(nullptr);
    Xn = 0;
    Yn = 0;
    Vx = V * cos(angle * M_PI / 180);
    Vy = V * sin(angle * M_PI / 180);

    QVector<double> x, y;
    int i = 0;

    if(ui->auto_scale->isChecked())
    {
        ui->Graph->xAxis->setRange(0, ((2 * Vy / g) * Vx) * 1.2);
        ui->Graph->yAxis->setRange(0, ((pow(Vy, 2) / (2 * g)) * 1.2));
    }
    else
    {
        ui->Graph->xAxis->setRange(0, ui->X_scale->text().toInt(nullptr, 10));
        ui->Graph->yAxis->setRange(0, ui->Y_scale->text().toInt(nullptr, 10));
    }

    while((Yn + Vy * dt) > 0)
    {
      x.resize(i + 1);
      y.resize(i + 1);

      Xn = Xn + Vx * dt;
      Yn = Yn + Vy * dt;
      Vy = Vy + (-g) * dt;

      x[i] = Xn;
      y[i] = Yn;


      ui->Graph->graph(0)->setData(x, y);
      ui->Graph->replot();

      usleep(dt*1 000 000);
      i++;
    }
}
