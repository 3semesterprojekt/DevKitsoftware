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
    void init(CurrentData*, control *);

private slots:
    void on_return_2_clicked();
    void on_overrideHeaterBox_toggled(bool checked);
    void on_overrideWindowBox_toggled(bool checked);
    void on_heaterButton_clicked();
    void on_windowButton_clicked();
    void on_waterButton_clicked();
    void on_waterSlider_valueChanged(int value);
    void waterdone();

private:
    Ui::SetManual *ui;
    CurrentData* ptr_currentdata;
    control* ptr_control;
    QTimer *timer;
};

#endif // SETMANUAL_H
