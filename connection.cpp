#include "connection.h"
#include <QDebug>

connection::connection()
{
    temp = 0;
    humidity = 0;
}


int connection::transfer(int device, int cmd){

    int res = 0;
    int spiDev;
    switch(device){
    case 0:
        spiDev = open("/dev/spidev1.0", O_RDWR);
        break;
    case 1:
        spiDev = open("/dev/spidev1.3", O_RDWR);
        break;
    default:
        qDebug() << "ERROR: wrong spidev device chosen! ";
        exit(0);
        //just hope it doesn't happend
        break;
    }

    //set commands using the tx buffer
    switch(cmd){
    case NOTHING: txbuffer[0] = 0x00;
        break;
    case OPENWINDOW: txbuffer[0] = 0x01;
        break;
    case CLOSEWINDOW: txbuffer[0] = 0x02;
        break;
    case STARTHEATER: txbuffer[0] = 0x03;
        break;
    case STOPHEATER: txbuffer[0] = 0x04;
        break;
    case ADDWATER: txbuffer[0] = 0x05;
        break;
    default: txbuffer[0] = 0x00;
        break;

    }
    txbuffer[1] = 0x00;
    txbuffer[2] = 0x00;
    txbuffer[3] = 0x00;

    int mode = SPI_MODE0;   //setting SPI mode
    ioctl(spiDev, SPI_IOC_WR_MODE, &mode);

    int lsb_setting = 0;    //0 means MSb first, 1 means LSb first
    ioctl(spiDev, SPI_IOC_WR_LSB_FIRST, &lsb_setting);

    int bits_per_word = 8; // 0 equals default (8)
    ioctl(spiDev, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word);

    struct spi_ioc_transfer xfer;
    memset(&xfer, 0, sizeof(xfer));

    xfer.tx_buf = (unsigned long)txbuffer;
    xfer.rx_buf = (unsigned long)rxbuffer;
    xfer.len = 4;
    xfer.speed_hz = 1 * 1000 * 1000;
    xfer.cs_change = 1;
    xfer.bits_per_word = bits_per_word;
    xfer.delay_usecs = 0; //todo: set correct delay
    res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);

    //get humidity and temperatur from rx buffer
    humidity = 0; //TODO: insert humidity from rx
    temp = 0; //TODO: insert temp from rx

    //qDebug() << "temp: " << temp;
    //qDebug() << "humidity: " << humidity;
    return 0;
}

int connection::getTemp(){
    return temp;
}

int connection::getHumidity(){
    return humidity;
}

void connection::getValues(int device){
    transfer(device, NOTHING);
    return;
}
void connection::setWindow(int device, bool state){
    if(state){
        transfer(device, OPENWINDOW);
    }
    else{
        transfer(device, CLOSEWINDOW);
    }
    return;
}

void connection::setHeater(int device, bool state){
    if(state){
        transfer(device, STARTHEATER);
    }
    else{
        transfer(device, STOPHEATER);
    }
    return;
}

void connection::giveWater(int device){
    transfer(device, ADDWATER);
    return;
}
