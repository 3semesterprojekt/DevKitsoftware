#include "setmanual.h"
#include "ui_setmanual.h"

SetManual::SetManual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetManual)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
}

SetManual::~SetManual()
{
    delete ui;
}

void SetManual::on_return_2_clicked()
{
    this->close();
}

void SetManual::init(CurrentData * ptr){
    ptr_currentdata = ptr;
    ui->windowButton->setEnabled(ptr_currentdata->getoverridewindow());
    ui->overrideWindowBox->setChecked(ptr_currentdata->getoverridewindow());
    ui->heaterButton->setEnabled(ptr_currentdata->getoverrideheater());
    ui->overrideHeaterBox->setChecked(ptr_currentdata->getoverrideheater());
    if(ptr_currentdata->getmanualheaterstate()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
    if(ptr_currentdata->getmanualwindowstate()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_overrideHeaterBox_toggled(bool checked)
{
    ui->heaterButton->setEnabled(checked);
    ptr_currentdata->setoverrideheater(checked);
}

void SetManual::on_overrideWindowBox_toggled(bool checked)
{
    ui->windowButton->setEnabled(checked);
    ptr_currentdata->setoverridewindow(checked);
}

void SetManual::on_heaterButton_clicked()
{
    ptr_currentdata->setmanualheaterstate(!ptr_currentdata->getmanualheaterstate());
    if(ptr_currentdata->getmanualheaterstate()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
}

void SetManual::on_windowButton_clicked()
{
    ptr_currentdata->setmanualwindowstate(!ptr_currentdata->getmanualwindowstate());
    if(ptr_currentdata->getmanualwindowstate()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_waterButton_clicked()
{
    ui->waterButton->setText("Adding Water ...");
    ui->waterButton->setEnabled(false);
    timer  = new QTimer(this);
    QTimer::singleShot(5000, this, SLOT(waterdone()));
}

void SetManual::on_waterSlider_valueChanged(int value)
{
    QString s = "Add ";
    s.append(QString::number(value));
    s.append("ml of water");
    ui->waterButton->setText(s);
}

void SetManual::waterdone(){
    QString s = "Add 0 ml of water ";
    ui->waterButton->setText(s);
    ui->waterButton->setEnabled(true);
    ui->waterSlider->setSliderPosition(0);

}
