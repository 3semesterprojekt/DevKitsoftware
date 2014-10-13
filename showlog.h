#ifndef SHOWLOG_H
#define SHOWLOG_H

#include <QWidget>
#include "logfile.h"

namespace Ui {
class showLog;
}

class showLog : public QWidget
{
    Q_OBJECT

public:
    explicit showLog(QWidget *parent = 0);
    ~showLog();
    void init(logFile*);

private slots:
    void on_returnButton_clicked();
    void on_clearLog_clicked();
    void update();

private:
    Ui::showLog *ui;
    logFile* ptr_logFile;
    unsigned int lastEntry;
};

#endif // SHOWLOG_H
