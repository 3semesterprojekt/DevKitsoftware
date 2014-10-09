#ifndef SHOWLOG_H
#define SHOWLOG_H

#include <QWidget>
#include "logfile.h"
#include <QTimer>

namespace Ui {
class showlog;
}

class showlog : public QWidget
{
    Q_OBJECT

public:
    explicit showlog(QWidget *parent = 0);
    ~showlog();
    void init(logfile*);

private slots:
    void on_return_2_clicked();
    void update();

    void on_clearlog_clicked();

private:
    Ui::showlog *ui;
    logfile* ptr_logfile;
    unsigned int lastEntry;
};

#endif // SHOWLOG_H
