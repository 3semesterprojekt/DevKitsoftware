#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif
    ui->label->setStyleSheet("QLabel {color : green;}");
    numberOfUnits = 1;
    ptr_logFile = new logFile;
    ptr_currentDataVector = new std::vector<CurrentData*>;
    ptr_currentDataVector->push_back(new CurrentData);
    ptr_currentDataVector->at(0)->setDeviceName("SPIDEV1.0");
    ptr_currentDataVector->at(0)->setDeviceID(0);
    ptr_control = new control;
    ptr_database = new Database;
    ptr_control->init(ptr_logFile,ptr_currentDataVector->at(0),ptr_database);
    ptr_bio = new ShowBiolex;
    ptr_bio->init(ptr_currentDataVector, ptr_database);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //connect(ptr_currentDataVector->at(0), SIGNAL(statusChanged()), this, SLOT(changeStatusLabel()));
    timer->start(10000); //every 10 second

    // get settargethumidity, min and max temp from local db and set
    // get window opened states from local db.

    ptr_database->SystemValuesInit(ptr_currentDataVector);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showData_clicked()
{
    ShowData* ptr_ShowData = new ShowData;
    ptr_ShowData->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ShowData->init(ptr_currentDataVector);
    ptr_ShowData->show();
}

void MainWindow::on_setManual_clicked()
{
    SetManual* ptr_SetManual = new SetManual;
    ptr_SetManual->setAttribute(Qt::WA_DeleteOnClose);
    ptr_SetManual->init(ptr_currentDataVector, ptr_control);
    ptr_SetManual->show();
}

void MainWindow::on_changeAuto_clicked()
{
    ChangeAuto* ptr_ChangeAuto = new ChangeAuto;
    ptr_ChangeAuto->setAttribute(Qt::WA_DeleteOnClose);
    ptr_ChangeAuto->init(ptr_currentDataVector, ptr_database);
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
    for(int i = 0; i < numberOfUnits; i++){
        ptr_control->updateSystemValues(i);
        ptr_control->autoTempControl(i);
        ptr_control->autoHumidityControl(i);
    }
}

void MainWindow::changeStatusLabel(){ //not currently in use
    QString tmp = "";

    if(ptr_currentDataVector->at(0)->getAutoTemp() == true){ //temp on auto
        tmp.append("Automatic Temperatur Control ON");
    }
    else{ //humidity control off
        tmp.append("Automatic Temperatur Control OFF");
    }

    if(ptr_currentDataVector->at(0)->getAutoHumidity() == true){ //humidity on auto
        tmp.append("Automatic Humidity Control ON");
    }
    else{ //humidity control off
        tmp.append("Automatic Humidity Control OFF");
    }

    if(ptr_currentDataVector->at(0)->getOverrideHeater() == true){
        tmp.append("Heater Override ON");
    }
    else{
        tmp.append("Heater Override OFF");
    }

    if(ptr_currentDataVector->at(0)->getOverrideWindow() == true){
        tmp.append("Window Override ON");
    }
    else{
        tmp.append("Window Override OFF");
    }

    ui->statusLabel->setText(tmp);
    return;
}

void MainWindow::on_showWeather_clicked()
{
    showWeather* ptr_ShowWeather = new showWeather;
    ptr_ShowWeather->setAttribute(Qt::WA_DeleteOnClose);

    ptr_ShowWeather->show();
}


void MainWindow::on_showBiolex_clicked()
{
    ShowBiolex* ptr_BioLex = new ShowBiolex;
    ptr_BioLex->setAttribute(Qt::WA_DeleteOnClose);
    ptr_BioLex->init(ptr_currentDataVector, ptr_database);
    ptr_BioLex->show();
}

void MainWindow::on_Settings_clicked()
{

}
