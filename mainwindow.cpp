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
    ptr_control = new control;
    ptr_control->init(ptr_logfile,ptr_currentdata);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000); //every 1 second
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
    ptr_SetManual->init(ptr_currentdata, ptr_control);
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
void MainWindow::update(){
    ptr_control->checkValues();
    //qDebug() << "VALUES:" << endl;
    //qDebug() << ptr_currentdata->getautotemp()<< endl;
    //qDebug() << ptr_currentdata->getautowater()<< endl;
    //qDebug() << ptr_currentdata->getcurrentheaterstate()<< endl;
    //qDebug() << ptr_currentdata->getcurrenttemp()<< endl;
    //qDebug() << ptr_currentdata->getcurrentwater()<< endl;
    //qDebug() << ptr_currentdata->getcurrentwindowstate()<< endl;
    //qDebug() << ptr_currentdata->getmanualheaterstate()<< endl;
    //qDebug() << ptr_currentdata->getmanualwindowstate()<< endl;
    //qDebug() << ptr_currentdata->getmaxtemp()<< endl;
    //qDebug() << ptr_currentdata->getmintemp()<< endl;
    //qDebug() << ptr_currentdata->getoverrideheater()<< endl;
    //qDebug() << ptr_currentdata->getoverrideheater()<< endl;
    //qDebug() << ptr_currentdata->getoverridewindow()<< endl;
    //qDebug() << ptr_currentdata->gettargetwater()<< endl;
}
