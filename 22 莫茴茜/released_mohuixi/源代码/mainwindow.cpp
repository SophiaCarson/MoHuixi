#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(pop()));
    newMethod();
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

void MainWindow::on_RdefaultB_3_clicked()
{
    ui->function->setText("sin x / x");
    ui->aLine->setText("0");
    ui->bLine->setText("1");
    ui->RorderLine->setText("0.0000001");
}

void MainWindow::on_RombergCal_3_clicked()
{
    double a = ui->aLine->text().toDouble();
    double b = ui->bLine->text().toDouble();
    double e = ui->RorderLine->text().toDouble();

    double T1,T2,S1,S2,C1,C2,R1,R2,h;
        int n=1,k,m=1;
        h=b-a;
        T1=0.5*h*(function(b)+function(a));

        while(m<=10)
            {
                double sum=0.0;
                for(k=0;k<n;k++)
                {
                    double x=a+(k+0.5)*h;
                    sum=sum+function(x);
                }
                n=n*2;
                h=h*0.5;
                T2=0.5*(T1+2*h*sum);
                ui->RresultLine->append(QString::number(T1,10,7));

                S1=(4*T2-T1)/3; //Sn = 4/3 T2n - 1/3 Tn

                ui->RresultLine->append(QString::number(S1,10,7));
                if(m==1)
                {
                    T1=T2;
                    ++m;
                    continue;
                }
                S2=(4*T2-T1)/3;
                C1=(16*S2-S1)/15; //Cn = 16/15 S2n - 1/15 Sn
                ui->RresultLine->append(QString::number(C1,10,7));
                if(m==2)
                {
                    S1=S2;
                    T1=T2;
                    ++m;
                    continue;
                }
                S2=(4*T2-T1)/3;
                C2=(16*S2-S1)/15;
                if(m==3)
                {
                    R1=(64*C2-C1)/63; //Rn = 64/63 C2n - 1/63 Cn
                    C1=C2;
                    S1=S2;
                    T1=T2;
                    ++m;
                    continue;
                }
                ui->RresultLine->append(QString::number(C1,10,7));
                if(m>=4)
                {
                    R2=(64*C2-C1)/63;
                    ui->RresultLine->append(QString::number(R1,10,7));
                    if(fabs(R2-R1)<e)
                        break;
                    R1=R2;
                    C1=C2;
                    S1=S2;
                    T1=T2;
                    ++m;
                }
            }

        ui->RresultLine->append("");
        ui->RresultLine->append(QString::number(m));
        ui->RresultLine->append(QString::number(R1,10,7));
}

double MainWindow::function(double x){
    if(x == 0.00)return 1;
    else
        return sin(x) / x;
}

void MainWindow::on_RclearB_3_clicked()
{
    ui->RresultLine->clear();
}

void MainWindow::pop()
{
    QMessageBox m(this);
    m.setWindowTitle("About NumericalAnalysis");
    m.setText("\n\nNumericalAnalysis 1.1.0\n\nBuilt on Oct 18 2018 13:10\n\nCopyright SophiaCarson Ltd. All rights reserved.\n\n");
    m.exec();
}

void MainWindow::newMethod(){
    double h;
    int a = 0;
    int b = 1;
    double T1,T2;
    int N = 2;
    cout<<N;
    double T[N+3],S[N+2],C[N+1],R[N];
    double sum,x;


    h=b-a;
    T2=T1=(function(a)+function(b))*h/2;
    for(int i=0;i<N+3;i++)
    {
        T[i]=T2;
        sum=0;
        x=a+h/2;
        while(x<b)
        {
            sum=function(x)+sum;
            x+=h;
        }
        T2=(T1+h*sum)/2;
        h=h/2;
        T1=T2;
        ui->RresultLine->append(QString::number(T[i],10,7));
    }
    ui->RresultLine->append("");

    for(int i=0;i<N+2;i++){
        S[i]=(4*T[i+1]-T[i])/3;
        ui->RresultLine->append(QString::number(S[i],10,7));
    }
    ui->RresultLine->append("");

    for(int i=0;i<N+1;i++){
        C[i]=(16*S[i+1]-S[i])/15;
        ui->RresultLine->append(QString::number(C[i],10,7));
    }
    ui->RresultLine->append("");

    for(int i=0;i<N;i++){
         R[i]=(64*C[i+1]-C[i])/63;
        ui->RresultLine->append(QString::number(R[i],10,7));
    }
    ui->RresultLine->append("");
}

