#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
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
    void init(std::vector<CurrentData*>*);

private slots:
    void on_returnButton_clicked();
    void update();

    void on_deviceComboBox_currentIndexChanged(int index);

private:
    Ui::ShowData *ui;
    CurrentData* ptr_currentData;
    std::vector<CurrentData*> *ptr_currentDataVector;
};

#endif // SHOWDATA_H
