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
    CurrentData* ptr_currentdata;
    logfile* ptr_logfile;
    control* ptr_control;

private slots:
    void on_showdata_clicked();
    void on_setmanual_clicked();
    void on_changeauto_clicked();
    void on_showlog_clicked();
    void update();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
