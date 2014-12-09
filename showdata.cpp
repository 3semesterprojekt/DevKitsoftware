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

void ShowData::init(std::vector<CurrentData*>* ptr){
    ptr_currentDataVector = ptr;
    for(unsigned int i = 0; i < ptr_currentDataVector->size(); i++){
        ui->deviceComboBox->addItem(ptr_currentDataVector->at(i)->getDeviceName());
    }
    ui->deviceComboBox->setCurrentIndex(0);
    ptr_currentData = ptr_currentDataVector->at(0);
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
    ui->outTempLcd->display(ptr_currentData->getCurrentOutTemp());
    connect(ptr_currentData, SIGNAL(currentDataChanged()), this, SLOT(update()));
}

void ShowData::update(){
    ui->tempLcd->display(ptr_currentData->getCurrentTemp());
    ui->humidityLcd->display(ptr_currentData->getCurrentHumidity());
    ui->outTempLcd->display(ptr_currentData->getCurrentOutTemp());
}

void ShowData::on_deviceComboBox_currentIndexChanged(int index)
{
        ptr_currentData = ptr_currentDataVector->at(index);
}
