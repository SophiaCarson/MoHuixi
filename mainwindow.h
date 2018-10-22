#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QMessageBox>
#include <QAction>
#include <math.h>
#include <iomanip>
#include <iostream>
#define EPS 1e-7
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_newtonCal_clicked();

    void on_clearB_clicked();

    void on_defaultB_clicked();

    bool isEmpty();

    bool isValid(vector<double> xv,vector<double> yv,int order);

    void on_RdefaultB_3_clicked();

    void on_RombergCal_3_clicked();

    void on_RclearB_3_clicked();

    void pop();

private:
    Ui::MainWindow *ui;
    double function(double x);
    void newMethod();
};

#endif // MAINWINDOW_H
