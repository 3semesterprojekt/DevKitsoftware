#include "showdatabase.h"
#include "ui_showdatabase.h"

ShowDatabase::ShowDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDatabase)
{
    ui->setupUi(this);
}

ShowDatabase::~ShowDatabase()
{
    delete ui;
}

void ShowDatabase::on_btn_autoconfig_clicked()
{

}
