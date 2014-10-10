#ifndef CHANGEAUTO_H
#define CHANGEAUTO_H

#include <QWidget>
#include "currentdata.h"

namespace Ui {
class ChangeAuto;
}

class ChangeAuto : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeAuto(QWidget *parent = 0);
    ~ChangeAuto();
    void init(CurrentData*);

private slots:
    void on_return_clicked();
    void on_humidityBox_toggled(bool checked);
    void on_tempBox_toggled(bool checked);
    void on_humiditySlider_valueChanged(int value);
    void on_maxTempSlider_valueChanged(int value);
    void on_minTempSlider_valueChanged(int value);

private:
    Ui::ChangeAuto *ui;
    void update();
    CurrentData* ptr_currentData;
};

#endif // CHANGEAUTO_H
