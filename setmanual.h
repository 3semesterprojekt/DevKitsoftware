#ifndef SETMANUAL_H
#define SETMANUAL_H

#include <QWidget>
#include "currentdata.h"
#include "control.h"
#include <QTimer>

namespace Ui {
class SetManual;
}

class SetManual : public QWidget
{
    Q_OBJECT

public:
    explicit SetManual(QWidget *parent = 0);
    ~SetManual();
    void init(std::vector<CurrentData*>*, control *);

private slots:
    void on_returnButton_clicked();
    void on_overrideHeaterBox_toggled(bool checked);
    void on_overrideWindowBox_toggled(bool checked);
    void on_heaterButton_clicked();
    void on_windowButton_clicked();
    void on_humidityButton_clicked();
    void on_humiditySlider_valueChanged(int value);
    void waterDone();

    void on_deviceComboBox_currentIndexChanged(int index);

private:
    Ui::SetManual *ui;
    CurrentData* ptr_currentData;
    std::vector<CurrentData*>* ptr_currentDataVector;
    control* ptr_control;
    int device;
};

#endif // SETMANUAL_H
