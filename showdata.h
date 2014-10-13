#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
#include <QTimer>
#include "currentdata.h"

namespace Ui {
class ShowData;
}

class ShowData : public QWidget
{
    Q_OBJECT

public:
    explicit ShowData(QWidget *parent = 0);
    ~ShowData();
    void init(CurrentData*);

private slots:
    void on_returnButton_clicked();
    void update();

private:
    Ui::ShowData *ui;
    CurrentData* ptr_currentData;
};

#endif // SHOWDATA_H
