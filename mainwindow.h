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
    CurrentData* ptr_currentData;
    logFile* ptr_logFile;
    control* ptr_control;

private slots:
    void on_showData_clicked();
    void on_setManual_clicked();
    void on_changeAuto_clicked();
    void on_showLog_clicked();
    void update();

    void on_showWeather_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
