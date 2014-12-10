#ifndef SHOWBIOLEX_H
#define SHOWBIOLEX_H
#include "changeauto.h"
#include "currentdata.h"
#include <QDialog>
#include <vector>
#include "database.h"

namespace Ui {
class ShowBiolex;
}

class Database;
class ShowBiolex : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBiolex(QWidget *parent = 0);
    ~ShowBiolex();

    void init(std::vector<CurrentData*>* ptr, Database* ptr2);

    void setHumMinMaxTemp(int humidity, int minTemp, int maxTemp);



private slots:
    void on_recbutton_clicked();

    void on_deviceComboBox_currentIndexChanged(int index);


    void on_ReturnButton_clicked();

    void on_plantCombo_currentIndexChanged(int index);

private:
    std::vector<CurrentData*>* ptr_currentDataVector;
    Ui::ShowBiolex *ui;
    int plantSwitch; // for switch
    CurrentData *ptr_currentData;
    Database* ptr_database;
    QString recommendationsTomato;
    QString recommendationsCucumber;
    QString recommendationsGrape;
    bool status;

};

#endif // SHOWBIOLEX_H
