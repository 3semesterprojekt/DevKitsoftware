#include "showdata.h"
#include "ui_showdata.h"

ShowData::ShowData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowData)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5000);
}

ShowData::~ShowData()
{
    delete ui;
}

void ShowData::on_return_clicked()
{
    this->close();
}

void ShowData::init(CurrentData* ptr){
    ptr_currentData = ptr;
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
}

void ShowData::update(){
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
}
