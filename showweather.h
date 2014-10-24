#ifndef SHOWWEATHER_H
#define SHOWWEATHER_H

#include <QWidget>

namespace Ui {
class showWeather;
}

class showWeather : public QWidget
{
    Q_OBJECT

public:
    explicit showWeather(QWidget *parent = 0);
    ~showWeather();

private slots:
    void on_returnButton_clicked();
    void loadImage();

private:
    Ui::showWeather *ui;

};

#endif // SHOWWEATHER_H
