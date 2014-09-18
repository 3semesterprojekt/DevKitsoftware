#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
    ui->label->setStyleSheet("QLabel {color : green;}");
    ptr_logfile = new logfile;
    ptr_currentdata = new CurrentData;
    ptr_logfile->setlogevent("hey it works");
    ptr_logfile->setlogevent("multiple times");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showdata_clicked()
{
    ShowData* ptr_ShowData = new ShowData;
    ptr_ShowData->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowData->init(ptr_currentdata);
    ptr_ShowData->show();
}

void MainWindow::on_setmanual_clicked()
{
    SetManual* ptr_SetManual = new SetManual;
    ptr_SetManual->setAttribute(Qt::WA_DeleteOnClose);
    ptr_SetManual->init(ptr_currentdata);
    ptr_SetManual->show();
}

void MainWindow::on_changeauto_clicked()
{
    ChangeAuto* ptr_ChangeAuto = new ChangeAuto;
    ptr_ChangeAuto->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ChangeAuto->init(ptr_currentdata);
    ptr_ChangeAuto->show();
}

void MainWindow::on_showlog_clicked()
{
    showlog* ptr_ShowLog = new showlog;
    ptr_ShowLog->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowLog->init(ptr_logfile);
    ptr_ShowLog->show();
}
