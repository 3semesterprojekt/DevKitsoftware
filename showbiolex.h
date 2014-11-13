#ifndef SHOWBIOLEX_H
#define SHOWBIOLEX_H
#include "changeauto.h"
#include "ui_changeauto.h"

#include "currentdata.h"
#include <QDialog>

namespace Ui {
class ShowBiolex;
}

class ShowBiolex : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBiolex(QWidget *parent = 0);
    ~ShowBiolex();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_recbutton_clicked();



private:
    Ui::ShowBiolex *ui;
    Ui::ChangeAuto *uiauto;
    int plantSwitch; // for switch
    CurrentData *ptr_currentData;
    QString recommendationsTomato;
    QString recommendationsCucumber;
    QString recommendationsGrape;
};

#endif // SHOWBIOLEX_H
