#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

#include <cmath>
#include <unistd.h>

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

    void on_Generate_clicked();

private:
    Ui::MainWindow *ui;
    void draw(void);
    bool stop;
    int angle;
    double dt;
    double V;
    double Xn;
    double Yn;
    double Vx;
    double Vy;
};

#endif // MAINWINDOW_H
