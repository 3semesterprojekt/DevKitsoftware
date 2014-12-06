#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "changeauto.h"
#include "setmanual.h"
#include "showdata.h"
#include "showlog.h"
#include "currentdata.h"
#include "logfile.h"
#include "control.h"
#include "showweather.h"
#include "showbiolex.h"
#include <QString>
#include <vector>
#include <QDebug>
#include "database.h"
#include "showbiolex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    logFile* ptr_logFile;
    control* ptr_control;
    int numberOfUnits;
    std::vector<CurrentData*> *ptr_currentDataVector;

    QSqlDatabase mydb;
    ShowBiolex* ptr_bio;
    CurrentData* ptr_currentData;
    Database* ptr_database;


private slots:
    void on_showData_clicked();
    void on_setManual_clicked();
    void on_changeAuto_clicked();
    void on_showLog_clicked();
    void update();
    void changeStatusLabel();
    void on_showWeather_clicked();
    void on_showBiolex_clicked();
    void on_Settings_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
