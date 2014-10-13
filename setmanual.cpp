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

void SetManual::on_returnButton_clicked()
{
    this->close();
}

void SetManual::init(CurrentData * ptr, control * ptr2){
    ptr_currentData = ptr;
    ptr_control = ptr2;
    ui->windowButton->setEnabled(ptr_currentData->getOverrideWindow());
    ui->overrideWindowBox->setChecked(ptr_currentData->getOverrideWindow());
    ui->heaterButton->setEnabled(ptr_currentData->getOverrideHeater());
    ui->overrideHeaterBox->setChecked(ptr_currentData->getOverrideHeater());
    if(ptr_currentData->getManualHeaterState()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
    if(ptr_currentData->getManualWindowState()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_overrideHeaterBox_toggled(bool checked)
{
    ui->heaterButton->setEnabled(checked);
    ptr_currentData->setOverrideHeater(checked);
}

void SetManual::on_overrideWindowBox_toggled(bool checked)
{
    ui->windowButton->setEnabled(checked);
    ptr_currentData->setOverrideWindow(checked);
}

void SetManual::on_heaterButton_clicked()
{
    ptr_currentData->setManualHeaterState(!ptr_currentData->getManualHeaterState());
    if(ptr_currentData->getManualHeaterState()){
        ui->heaterButton->setText("Stop Heater");
    }
    else{
        ui->heaterButton->setText("Start Heater");
    }
}

void SetManual::on_windowButton_clicked()
{
    ptr_currentData->setManualWindowState(!ptr_currentData->getManualWindowState());
    if(ptr_currentData->getManualWindowState()){
        ui->windowButton->setText("Close Windows");
    }
    else{
        ui->windowButton->setText("Open Windows");
    }
}

void SetManual::on_humidityButton_clicked()
{
    ptr_control->dispenseWater(ui->humiditySlider->value());
    ui->humidityButton->setText("Adding Water ...");
    ui->humidityButton->setEnabled(false);
    timer  = new QTimer(this);
    QTimer::singleShot(5000, this, SLOT(waterDone()));
}

void SetManual::on_humiditySlider_valueChanged(int value)
{
    QString s = "Add ";
    s.append(QString::number(value));
    s.append("ml of water");
    ui->humidityButton->setText(s);
}

void SetManual::waterDone(){
    QString s = "Add 0 ml of water ";
    ui->humidityButton->setText(s);
    ui->humidityButton->setEnabled(true);
    ui->humiditySlider->setSliderPosition(0);

}
