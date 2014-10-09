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

void SetManual::init(CurrentData * ptr, control * ptr2){
    ptr_currentdata = ptr;
    ptr_control = ptr2;
    ui->windowButton->setEnabled(ptr_currentdata->getOverrideWindow());
    ui->overrideWindowBox->setChecked(ptr_currentdata->getOverrideWindow());
    ui->heaterButton->setEnabled(ptr_currentdata->getOverrideHeater());
    ui->overrideHeaterBox->setChecked(ptr_currentdata->getOverrideHeater());
    if(ptr_currentdata->getManualHeaterState()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
    if(ptr_currentdata->getManualWindowState()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_overrideHeaterBox_toggled(bool checked)
{
    ui->heaterButton->setEnabled(checked);
    ptr_currentdata->setOverrideHeater(checked);
}

void SetManual::on_overrideWindowBox_toggled(bool checked)
{
    ui->windowButton->setEnabled(checked);
    ptr_currentdata->setOverrideWindow(checked);
}

void SetManual::on_heaterButton_clicked()
{
    ptr_currentdata->setManualHeaterState(!ptr_currentdata->getManualHeaterState());
    if(ptr_currentdata->getManualHeaterState()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
}

void SetManual::on_windowButton_clicked()
{
    ptr_currentdata->setManualWindowState(!ptr_currentdata->getManualWindowState());
    if(ptr_currentdata->getManualWindowState()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_waterButton_clicked()
{
    ptr_control->dispenseWater(ui->waterSlider->value());
    ui->waterButton->setText("Adding Water ...");
    ui->waterButton->setEnabled(false);
    timer  = new QTimer(this);
    QTimer::singleShot(5000, this, SLOT(waterDone()));
}

void SetManual::on_waterSlider_valueChanged(int value)
{
    QString s = "Add ";
    s.append(QString::number(value));
    s.append("ml of water");
    ui->waterButton->setText(s);
}

void SetManual::waterDone(){
    QString s = "Add 0 ml of water ";
    ui->waterButton->setText(s);
    ui->waterButton->setEnabled(true);
    ui->waterSlider->setSliderPosition(0);

}
