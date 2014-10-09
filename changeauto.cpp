#include "changeauto.h"
#include "ui_changeauto.h"

ChangeAuto::ChangeAuto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeAuto)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
}

ChangeAuto::~ChangeAuto()
{
    delete ui;
}

void ChangeAuto::init(CurrentData *ptr){
    ptr_currentdata = ptr;
    ui->templabel->setText("minimum temperatur");
    ui->templcd->display(ptr_currentdata->getMinTemp());
    ui->mintempSlider->setSliderPosition(ptr_currentdata->getMinTemp());
    ui->maxtempSlider->setSliderPosition(ptr_currentdata->getMaxTemp());
    ui->ohmlcd->display(ptr_currentdata->getTargetHumidity());
    ui->ohmSlider->setSliderPosition(ptr_currentdata->getTargetHumidity());
    ui->ohmBox->setChecked(ptr_currentdata->getAutoHumidity());
    ui->tempBox->setChecked(ptr_currentdata->getAutoTemp());
}
void ChangeAuto::update(){


}

void ChangeAuto::on_return_2_clicked()
{
    this->close();
}

void ChangeAuto::on_ohmBox_toggled(bool checked)
{
    ptr_currentdata->setAutoHumidity(checked);
}

void ChangeAuto::on_tempBox_toggled(bool checked)
{
    ptr_currentdata->setAutoTemp(checked);
}

void ChangeAuto::on_ohmSlider_valueChanged(int value)
{
    ptr_currentdata->setTargetHumidity(value);
    ui->ohmlcd->display(ptr_currentdata->getTargetHumidity());
}

void ChangeAuto::on_maxtempSlider_valueChanged(int value)
{
    if(ptr_currentdata->getMinTemp()>value){
        ptr_currentdata->setMaxTemp(ptr_currentdata->getMinTemp());
        ui->maxtempSlider->setSliderPosition(ptr_currentdata->getMaxTemp());
    }
    else{
        ptr_currentdata->setMaxTemp(value);
    }
    ui->templabel->setText("maximum temperatur");
    ui->templcd->display(ptr_currentdata->getMaxTemp());
}

void ChangeAuto::on_mintempSlider_valueChanged(int value)
{
    if(ptr_currentdata->getMaxTemp()<value){
        ptr_currentdata->setMinTemp(ptr_currentdata->getMaxTemp());
        ui->mintempSlider->setSliderPosition(ptr_currentdata->getMinTemp());
    }
    else{
        ptr_currentdata->setMinTemp(value);
    }
    ui->templabel->setText("minimum temperatur");
    ui->templcd->display(ptr_currentdata->getMinTemp());
}
