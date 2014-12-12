#ifndef SHOWDATABASE_H
#define SHOWDATABASE_H

#include <QString>
#include <QWidget>

namespace Ui {
class ShowDatabase;
}

class ShowDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit ShowDatabase(QWidget *parent = 0);
    ~ShowDatabase();

    void Init();

private slots:
    void on_btn_autoconfig_clicked();

    void on_btn_return_clicked();

    void on_btn_measurement_clicked();

    void on_btn_sensor_clicked();

    void on_btn_clearTable_clicked();

    void on_System_clicked();

private:
    Ui::ShowDatabase *ui;

    QString table;
};

#endif // SHOWDATABASE_H
