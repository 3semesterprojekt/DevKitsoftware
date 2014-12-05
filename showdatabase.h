#ifndef SHOWDATABASE_H
#define SHOWDATABASE_H

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

private slots:
    void on_btn_autoconfig_clicked();

private:
    Ui::ShowDatabase *ui;
};

#endif // SHOWDATABASE_H
