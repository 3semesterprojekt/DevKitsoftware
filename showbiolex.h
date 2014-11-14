#ifndef SHOWBIOLEX_H
#define SHOWBIOLEX_H
#include "changeauto.h"
#include "currentdata.h"
#include <QDialog>
#include <vector>

namespace Ui {
class ShowBiolex;
}

class ShowBiolex : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBiolex(QWidget *parent = 0);
    ~ShowBiolex();

    void init(std::vector<CurrentData*>*);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_recbutton_clicked();



    void on_deviceComboBox_currentIndexChanged(int index);

private:
    std::vector<CurrentData*>* ptr_currentDataVector;
    Ui::ShowBiolex *ui;
    int plantSwitch; // for switch
    CurrentData *ptr_currentData;
    QString recommendationsTomato;
    QString recommendationsCucumber;
    QString recommendationsGrape;
    bool status;
};

#endif // SHOWBIOLEX_H
