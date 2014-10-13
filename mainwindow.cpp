#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
    ui->label->setStyleSheet("QLabel {color : green;}");
    ptr_logFile = new logFile;
    ptr_currentData = new CurrentData;
    ptr_control = new control;
    ptr_control->init(ptr_logFile,ptr_currentData);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000); //every 1 second
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showData_clicked()
{
    ShowData* ptr_ShowData = new ShowData;
    ptr_ShowData->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowData->init(ptr_currentData);
    ptr_ShowData->show();
}

void MainWindow::on_setManual_clicked()
{
    SetManual* ptr_SetManual = new SetManual;
    ptr_SetManual->setAttribute(Qt::WA_DeleteOnClose);
    ptr_SetManual->init(ptr_currentData, ptr_control);
    ptr_SetManual->show();
}

void MainWindow::on_changeAuto_clicked()
{
    ChangeAuto* ptr_ChangeAuto = new ChangeAuto;
    ptr_ChangeAuto->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ChangeAuto->init(ptr_currentData);
    ptr_ChangeAuto->show();
}

void MainWindow::on_showLog_clicked()
{
    showLog* ptr_ShowLog = new showLog;
    ptr_ShowLog->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowLog->init(ptr_logFile);
    ptr_ShowLog->show();
}
void MainWindow::update(){
    ptr_control->checkValues();
    //qDebug() << "VALUES:" << endl;
    //qDebug() << ptr_currentData->getautotemp()<< endl;
    //qDebug() << ptr_currentData->getautowater()<< endl;
    //qDebug() << ptr_currentData->getcurrentheaterstate()<< endl;
    //qDebug() << ptr_currentData->getcurrenttemp()<< endl;
    //qDebug() << ptr_currentData->getcurrentwater()<< endl;
    //qDebug() << ptr_currentData->getcurrentwindowstate()<< endl;
    //qDebug() << ptr_currentData->getmanualheaterstate()<< endl;
    //qDebug() << ptr_currentData->getmanualwindowstate()<< endl;
    //qDebug() << ptr_currentData->getmaxtemp()<< endl;
    //qDebug() << ptr_currentData->getmintemp()<< endl;
    //qDebug() << ptr_currentData->getoverrideheater()<< endl;
    //qDebug() << ptr_currentData->getoverrideheater()<< endl;
    //qDebug() << ptr_currentData->getoverridewindow()<< endl;
    //qDebug() << ptr_currentData->gettargetwater()<< endl;
}

void MainWindow::on_showWeather_clicked()
{
    showWeather* ptr_ShowWeather = new showWeather;
    ptr_ShowWeather->setAttribute(Qt::WA_DeleteOnClose);

    ptr_ShowWeather->show();
}
