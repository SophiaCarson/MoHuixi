#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isEmpty(){
    if(ui->orderLine->text().isEmpty()||ui->xLine->text().isEmpty()||ui->yLine->text().isEmpty()){
        ui->resultLine->append("X/Y/Order is empty!!!");
        return false;
    }else return true;
}

bool MainWindow::isValid(vector<double> xv,vector<double> yv,int order){
    if(xv.size()!=yv.size()||order<=0){
        ui->resultLine->append("X/Y/Order is invalid!!!");
        return false;
    }else return true;
}

void MainWindow::on_newtonCal_clicked()
{

    QString tmp = "1";
    QString tp = "2";
    bool *ok;
    vector<double> xv;
    vector<double> yv;
    int order;

    if(!isEmpty()){

    }else{
        for(int i = 0; tmp!=0; i++){
           tmp = ui->xLine->text().section(",",i,i);
           xv.push_back(tmp.toDouble(ok));
        }//0.4,0.55,0.65,0.80,0.90,1.05

        for(int i = 0; tp!=0;i++){
            tp = ui->yLine->text().section(",",i,i);
            yv.push_back(tp.toDouble(ok));
        }//0.41075,0.57815,0.69675,0.88811,1.02652,1.25382

        order = ui->orderLine->text().toInt();

        if(isValid(xv,yv,order)){
            int i = 0;
            int j;
            vector<double> data(order*(order+1),0);
            vector<double> print;

            while(i < order){
                j = order;
                while(j > i){
                    if(i==0){
                        data[j] = ((yv[j]-yv[j-1])/(xv[j]-xv[j-1]));
                    }else{
                        data[j] = (data[j]-data[j-1])/(xv[j]-xv[j-1-i]);
                    }
                    print.push_back(data[j]);
                    j--;
                }
                i++;
            }

           for(int count=0;count<order+1;count++){
               if(count!=0){
                    ui->resultLine->append("");
                   ui->resultLine->insertPlainText(QString::number(xv[count],10,2)+"     "+QString::number(yv[count],10,5)+"        ");

                    int p=5;
                    int tt = order-count-1+1;
                    for(int t=0;t+1<=count;t++){
                        ui->resultLine->insertPlainText(QString::number(print[tt],10,5)+"     ");
                        tt = tt+p;
                        p--;
                    }
                }
               if(count==0){
                   ui->resultLine->append(QString::number(xv[count],10,2)+"     "+QString::number(yv[count],10,5)+"        ");
               }
           }
        }else{

        }
    }
}

void MainWindow::on_clearB_clicked()
{
    ui->resultLine->clear();
}

void MainWindow::on_defaultB_clicked()
{
    ui->xLine->setText("0.4,0.55,0.65,0.80,0.90,1.05");
    ui->yLine->setText("0.41075,0.57815,0.69675,0.88811,1.02652,1.25382");
    ui->orderLine->setText("5");
}
