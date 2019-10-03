#include "mainwindow.h"
#include "ui_mainwindow.h"

#define g 9.80665

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    angle = 0;      //zeruje wszystkie zmienne
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

void MainWindow::on_Generate_clicked()
{
    QVector<double> x, y;
    int i = 0;

    angle = ui->angle_edit->text().toInt(nullptr, 10);
    dt = ui->dt_edit->text().toDouble(nullptr);
    V = ui->V_edit->text().toDouble(nullptr);
    Xn = 0;
    Yn = 0;
    Vx = V * cos(angle * M_PI / 180);
    Vy = V * sin(angle * M_PI / 180);

    ui->Graph->xAxis->setRange(0, ui->X_scale->text().toInt(nullptr, 10));
    ui->Graph->yAxis->setRange(0, ui->Y_scale->text().toInt(nullptr, 10));

    while(Yn >= 0)
    {
      x.resize(i + 1);
      y.resize(i + 1);

      Xn = Xn + Vx * dt;
      Yn = Yn + Vy * dt;
      Vy = Vy + (-g) * dt;

      x[i] = Xn;
      y[i] = Yn;

      QCPItemLine *arrowX = new QCPItemLine(ui->Graph);
      arrowX->start->setCoords(Xn, Yn);
      arrowX->end->setCoords(Xn + Vx/5, Yn);
      arrowX->setHead(QCPLineEnding::esSpikeArrow);

      QCPItemLine *arrowY = new QCPItemLine(ui->Graph);
      arrowY->start->setCoords(Xn, Yn);
      arrowY->end->setCoords(Xn, Yn + Vy/5);
      arrowY->setHead(QCPLineEnding::esSpikeArrow);

      ui->Graph->graph(0)->setData(x, y);
      ui->Graph->replot();

      ui->V_value->setNum(sqrt(Vx*Vx + Vy*Vy));
      ui->Vy_value->setNum(Vy);
      ui->Vx_value->setNum(Vx);

      delete arrowX;
      delete arrowY;
      i++;
    }
}
