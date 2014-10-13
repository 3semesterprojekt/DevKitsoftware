#include "changeauto.h"
#include "ui_changeauto.h"

ChangeAuto::ChangeAuto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeAuto)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif
}

ChangeAuto::~ChangeAuto()
{
    delete ui;
}

void ChangeAuto::init(CurrentData *ptr){
    ptr_currentData = ptr;
    ui->templabel->setText("minimum temperatur");
    ui->tempLcd->display(ptr_currentData->getMinTemp());
    ui->minTempSlider->setSliderPosition(ptr_currentData->getMinTemp());
    ui->maxTempSlider->setSliderPosition(ptr_currentData->getMaxTemp());
    ui->humidityLcd->display(ptr_currentData->getTargetHumidity());
    ui->humiditySlider->setSliderPosition(ptr_currentData->getTargetHumidity());
    ui->humidityBox->setChecked(ptr_currentData->getAutoHumidity());
    ui->tempBox->setChecked(ptr_currentData->getAutoTemp());
}
void ChangeAuto::update(){


}

void ChangeAuto::on_returnButton_clicked()
{
    this->close();
}

void ChangeAuto::on_humidityBox_toggled(bool checked)
{
    ptr_currentData->setAutoHumidity(checked);
}

void ChangeAuto::on_tempBox_toggled(bool checked)
{
    ptr_currentData->setAutoTemp(checked);
}

void ChangeAuto::on_humiditySlider_valueChanged(int value)
{
    ptr_currentData->setTargetHumidity(value);
    ui->humidityLcd->display(ptr_currentData->getTargetHumidity());
}

void ChangeAuto::on_maxTempSlider_valueChanged(int value)
{
    if(ptr_currentData->getMinTemp()>value){
        ptr_currentData->setMaxTemp(ptr_currentData->getMinTemp());
        ui->maxTempSlider->setSliderPosition(ptr_currentData->getMaxTemp());
    }
    else{
        ptr_currentData->setMaxTemp(value);
    }
    ui->templabel->setText("maximum temperatur");
    ui->tempLcd->display(ptr_currentData->getMaxTemp());
}

void ChangeAuto::on_minTempSlider_valueChanged(int value)
{
    if(ptr_currentData->getMaxTemp()<value){
        ptr_currentData->setMinTemp(ptr_currentData->getMaxTemp());
        ui->minTempSlider->setSliderPosition(ptr_currentData->getMinTemp());
    }
    else{
        ptr_currentData->setMinTemp(value);
    }
    ui->templabel->setText("minimum temperatur");
    ui->tempLcd->display(ptr_currentData->getMinTemp());
}
