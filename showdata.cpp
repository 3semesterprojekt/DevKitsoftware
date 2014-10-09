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

void ShowData::on_return_2_clicked()
{
    this->close();
}

void ShowData::init(CurrentData* ptr){
    ptr_currentdata = ptr;
    ui->templcd->display(ptr_currentdata->getCurrentTemp());
    ui->ohmlcd->display(ptr_currentdata->getCurrentHumidity());
}

void ShowData::update(){
    ui->templcd->display(ptr_currentdata->getCurrentTemp());
    ui->ohmlcd->display(ptr_currentdata->getCurrentHumidity());
}
