#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <vector>
#include <iostream>
#include <QMessageBox>
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
