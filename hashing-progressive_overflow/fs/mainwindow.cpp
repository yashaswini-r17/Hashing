#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QMessageBox>
//#include <QLabel>
//#include <QTimer>
//#include <QThread>
//#include <QTabWidget>
//#include <QTabBar>
#include<QIntValidator>

#include "code.h"

Hashtable ht(50);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_2);
    ui->label_17->clear();
}

void MainWindow::on_pushButton_clicked()
{

    if(ui->lineEdit->text()!="" && ui->lineEdit_2->text()!="" && ui->lineEdit_3->text()!="" && ui->lineEdit_4->text()!="")
    {
    ui->lineEdit->setValidator( new QIntValidator);
    ui->lineEdit_4->setValidator( new QIntValidator);
    int key=ui->lineEdit->text().toInt();
    string value=ui->lineEdit_2->text().toStdString();
    string brn=ui->lineEdit_3->text().toStdString();
    string sem=ui->lineEdit_4->text().toStdString();
    int r=ht.insert(key,value,brn,sem);

    if(r==-1)
        ui->label_5->setText("Storage is Full!!");
    else if(r==-2)
        ui->label_5->setText("Duplicate entry!!");
    else if(r==-3)
        ui->label_5->setText("Enter a valid number for usn!!");
    else
        ui->label_5->setText("Insertion Successfull!!");
    }
    else
        ui->label_5->setText("Enter sufficient data!!");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label_17->clear();
    int i=ht.display();
    if(i==-1)
        ui->textEdit->setText("No records to display");
    else
    {
        ui->textEdit->setText("USN\t\tNAME\t\tBRANCH\t\tSEM\n");
        for(int i=0;i<ht.size;i++)
                {
                    if(ht.arr[i]!=nullptr)
                       {
                        int add=atoi(indexadd[i]);
                        ht.unpack(add);
                        QString usn=u,name=n,branch=brn,semester=sem;
                        ui->textEdit->append( usn + "\t\t"+name+"\t\t"+branch+"\t\t"+semester+"\n" );
                        //QString text="usn ="+usn+"\tname="+name+"\tbranch:"+branch+"\tsem:"+semester+"\n";
                    }
    }
    }
    ui->tabWidget->setCurrentWidget(ui->tab_3);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->lineEdit_5->text()!="")
    {
    int key=ui->lineEdit_5->text().toInt();
    int val=ht.search(key);
    if(val==0)
    {
        ui->label_8->setText("Record Not Found!");
        ui->label_11->setText("");
    }
    else if(val==-3)
    {
        ui->label_8->setText("Enter valid usn!");
        ui->label_11->setText("");
    }
     else if(val==1)
        {
            int add=atoi(indexadd[ht.hashindex]);
            ht.unpack(add);
            ui->label_8->setText("Record Found!");
            QString usn=u,name=n,branch=brn,semester=sem;
            ui->label_11->setText("USN: "+usn+"\nNAME: "+name+"\nBRANCH: "+branch+"\nSEM: "+semester);
        }
    }
    else
    {
        ui->label_8->setText("Enter USN!");
        ui->label_11->setText("");
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->lineEdit_6->text()!="")
    {
    int key=ui->lineEdit_6->text().toInt();
    int val=ht.deletestud(key);
    if(val==-1)
        ui->label_10->setText("No Records present!");
    else if(val==-2)
        ui->label_10->setText("Record with usn "+ui->lineEdit_6->text()+" not found!");
    else if(val==-3)
        ui->label_10->setText("Enter valid usn!");
    else
        ui->label_10->setText("Record Deleted Successfully");
    }
    else
        ui->label_10->setText("Enter USN!");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_4);
    ui->label_17->clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_5);
    ui->label_17->clear();
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->label_5->clear();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
    on_pushButton_8_clicked();
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit_5->setText("");
    ui->label_8->clear();
    ui->label_11->clear();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit_6->setText("");
    ui->label_10->clear();
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
    on_pushButton_10_clicked();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
    on_pushButton_11_clicked();
}

void MainWindow::on_pushButton_15_clicked()
{
    if(ui->lineEdit_7->text()!="")
    {
    int key=ui->lineEdit_7->text().toInt();
    int val=ht.search(key);
    if(val==0)
        ui->label_13->setText("Record Not Found!");
    else if(val==-3)
        ui->label_13->setText("Enter valid usn!");
     else
        {
            int add=atoi(indexadd[ht.hashindex]);
            ht.unpack(add);
            QString usn=u,name=n,branch=brn,semester=sem;
            ui->lineEdit->setText(usn);
            ui->lineEdit_2->setText(name);
            ui->lineEdit_3->setText(branch);
            ui->lineEdit_4->setText(semester);
            ui->label_5->clear();
            ht.deletestud(key);
            ui->tabWidget->setCurrentWidget(ui->tab_2);
            on_pushButton_16_clicked();
        }
    }
    else
        ui->label_13->setText("Enter USN!");
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_6);
    ui->label_17->clear();
}

void MainWindow::on_pushButton_19_clicked()
{
    if(ui->lineEdit_8->text()=="ADMIN" && ui->lineEdit_9->text()=="ADMIN")
    {

        ui->label_17->setText("Login Successful!!");


        ui->tabWidget->setCurrentWidget(ui->tab);
        ht.recovery();

        //QThread::msleep(1000);
    }
    else
    {
        ui->label_16->setText("Invalid Username or Password!! Try Again");
        //QTimer::singleShot(2000,ui->label_16,SLOT(hide()));
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    on_pushButton_16_clicked();
    ui->tabWidget->setCurrentWidget(ui->tab);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->lineEdit_7->setText("");
    ui->label_13->clear();
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_7);
    on_pushButton_20_clicked();
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->lineEdit_8->setText("");
    ui->lineEdit_9->setText("");
    ui->label_16->setText("");
}

