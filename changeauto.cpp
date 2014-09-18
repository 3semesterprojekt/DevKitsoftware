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
    ui->templcd->display(ptr_currentdata->getmintemp());
    ui->mintempSlider->setSliderPosition(ptr_currentdata->getmintemp());
    ui->maxtempSlider->setSliderPosition(ptr_currentdata->getmaxtemp());
    ui->ohmlcd->display(ptr_currentdata->gettargetwater());
    ui->ohmSlider->setSliderPosition(ptr_currentdata->gettargetwater());
    ui->ohmBox->setChecked(ptr_currentdata->getautowater());
    ui->tempBox->setChecked(ptr_currentdata->getautotemp());
}
void ChangeAuto::update(){


}

void ChangeAuto::on_return_2_clicked()
{
    this->close();
}

void ChangeAuto::on_ohmBox_toggled(bool checked)
{
    ptr_currentdata->setautowater(checked);
}

void ChangeAuto::on_tempBox_toggled(bool checked)
{
    ptr_currentdata->setautotemp(checked);
}

void ChangeAuto::on_ohmSlider_valueChanged(int value)
{
    ptr_currentdata->settargetwater(value);
    ui->ohmlcd->display(ptr_currentdata->gettargetwater());
}

void ChangeAuto::on_maxtempSlider_valueChanged(int value)
{
    if(ptr_currentdata->getmintemp()>value){
        ptr_currentdata->setmaxtemp(ptr_currentdata->getmintemp());
        ui->maxtempSlider->setSliderPosition(ptr_currentdata->getmaxtemp());
    }
    else{
        ptr_currentdata->setmaxtemp(value);
    }
    ui->templabel->setText("maximum temperatur");
    ui->templcd->display(ptr_currentdata->getmaxtemp());
}

void ChangeAuto::on_mintempSlider_valueChanged(int value)
{
    if(ptr_currentdata->getmaxtemp()<value){
        ptr_currentdata->setmintemp(ptr_currentdata->getmaxtemp());
        ui->mintempSlider->setSliderPosition(ptr_currentdata->getmintemp());
    }
    else{
        ptr_currentdata->setmintemp(value);
    }
    ui->templabel->setText("minimum temperatur");
    ui->templcd->display(ptr_currentdata->getmintemp());
}
