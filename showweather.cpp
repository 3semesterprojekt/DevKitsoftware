#include "showweather.h"
#include "ui_showweather.h"
#include "filedownloader.h"
FileDownloader* m_pFile;

showWeather::showWeather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showWeather)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif


    QUrl imageUrl("http://www.dmi.dk/uploads/tx_dmidatastore/webservice/k/d/_/n/g/femdgn_dk.png");
    m_pFile = new FileDownloader(imageUrl,this);//download image
    connect(m_pFile,SIGNAL(downloaded()),SLOT(loadImage()));

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
    Image.loadFromData(m_pFile->downloadedData());
    int i = 5;
    Image.scaledToHeight(i);
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(Image);

}



