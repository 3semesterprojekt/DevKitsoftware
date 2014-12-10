#include "showdatabase.h"
#include "ui_showdatabase.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "database.h"
#include "QSqlDatabase"

ShowDatabase::ShowDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDatabase)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif
    ui->btn_clearTable->isEnabled()== false;
}

void ShowDatabase::Init()
{

}

ShowDatabase::~ShowDatabase()
{
    delete ui;
}

void ShowDatabase::on_btn_return_clicked()
{
        this->close();
}

void ShowDatabase::on_btn_autoconfig_clicked()
{
    ui->btn_clearTable->isEnabled()== true;
    table = "AutoConfig";
    QSqlQueryModel* model = new QSqlQueryModel;

    QSqlQuery qry;
    qry.exec("SELECT * FROM AutoConfig");
    qDebug() << "Autoconfig table read" << qry.lastError();

    model->setQuery(qry);
    ui->tableView->setModel(model);
    QHeaderView* qheader;
    ui->tableView->horizontalHeader()->setResizeMode(qheader->ResizeToContents);
}

void ShowDatabase::on_btn_measurement_clicked()
{
    ui->btn_clearTable->isEnabled()== true;
    table = "Measurement";
    QSqlQueryModel* model = new QSqlQueryModel;

    QSqlQuery qry;
    qry.exec("SELECT * FROM Measurement");
    qDebug() << "Measurement table read" << qry.lastError();

    model->setQuery(qry);
    ui->tableView->setModel(model);
    QHeaderView* qheader;
    ui->tableView->horizontalHeader()->setResizeMode(qheader->ResizeToContents);

}

void ShowDatabase::on_btn_sensor_clicked()
{
    ui->btn_clearTable->isEnabled()== true;
    table= "Sensor";
    QSqlQueryModel* model = new QSqlQueryModel;

    QSqlQuery qry;
    qry.exec("SELECT * FROM Sensor");
    qDebug() << "Sensor table read" << qry.lastError();

    model->setQuery(qry);
    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(0,Qt::DescendingOrder);


    QHeaderView* qheader;
    ui->tableView->horizontalHeader()->setResizeMode(qheader->ResizeToContents);
}

void ShowDatabase::on_btn_clearTable_clicked()
{
    QSqlQuery qry;
    if(table=="Sensor")
        qry.exec("DELETE FROM Sensor");
    if(table == "Measurement")
        qry.exec("DELETE FROM Measurement");
    if(table == "AutoConfig")
        qry.exec("DELETE FROM AutoConfig");

}
