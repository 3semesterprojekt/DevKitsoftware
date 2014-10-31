#include "showweather.h"
#include "ui_showweather.h"
#include "filedownloader.h"
FileDownloader* m_pImgCtrl;

showWeather::showWeather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showWeather)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif


    QUrl imageUrl("http://www.dmi.dk/uploads/tx_dmidatastore/webservice/k/d/_/n/g/femdgn_dk.png");
    m_pImgCtrl = new FileDownloader(imageUrl,this);//download image
    connect(m_pImgCtrl,SIGNAL(downloaded()),SLOT(loadImage()));

}

showWeather::~showWeather()
{
    delete ui;
}

void showWeather::on_returnButton_clicked()
{
    this->close();
}

void showWeather::loadImage()
{
    QPixmap Image;
    Image.loadFromData(m_pImgCtrl->downloadedData());
    int i = 5;
    Image.scaledToHeight(i);
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(Image);

}



