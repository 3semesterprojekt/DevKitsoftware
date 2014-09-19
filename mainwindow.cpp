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
    QTimer *timer = new QTimer(this);                           //Timer til at hente data
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));    //fra systemet og tilpasse
    timer->start(10000);                                        //dem alle 10 sekunder
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showdata_clicked()      //aabner et vindue hvor brugeren kan se de maalte data
{
    ShowData* ptr_ShowData = new ShowData;
    ptr_ShowData->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowData->init(ptr_currentdata);
    ptr_ShowData->show();
}

void MainWindow::on_setmanual_clicked()     //aabner et vindue hvor brugeren kan override systemets automatiske handlinger
{
    SetManual* ptr_SetManual = new SetManual;
    ptr_SetManual->setAttribute(Qt::WA_DeleteOnClose);
    ptr_SetManual->init(ptr_currentdata);
    ptr_SetManual->show();
}

void MainWindow::on_changeauto_clicked()    //aabner et vindue hvor brugeren kan instille systemets taget vaerdier
{
    ChangeAuto* ptr_ChangeAuto = new ChangeAuto;
    ptr_ChangeAuto->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ChangeAuto->init(ptr_currentdata);
    ptr_ChangeAuto->show();
}

void MainWindow::on_showlog_clicked()   //aabner et vindue hvor brugeren kan se et log over alle (vigtige) systemhandlinger
{
    showlog* ptr_ShowLog = new showlog;
    ptr_ShowLog->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowLog->init(ptr_logfile);
    ptr_ShowLog->show();
}
void MainWindow::update(){      //maaler vaerdierne og tilpasser systemets status derefter (vinduer/varme/vand)
    ptr_control->checkvalues();
}
