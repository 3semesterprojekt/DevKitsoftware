#include "showdata.h"
#include "ui_showdata.h"

ShowData::ShowData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowData)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif
}

ShowData::~ShowData()
{
    delete ui;
}

void ShowData::on_returnButton_clicked()
{
    this->close();
}

void ShowData::init(CurrentData* ptr){
    ptr_currentData = ptr;
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
    connect(ptr_currentData, SIGNAL(currentDataChanged()), this, SLOT(update()));
}

void ShowData::update(){
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
}
