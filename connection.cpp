#include "connection.h"
#include <QDebug>

connection::connection()
{
}


int connection::transfer(int device, int cmd){

    int res = 0;
    int spiDev;
    int len = 4;
    if(device == 1){
        spiDev = open("/dev/spidev1.0", O_RDWR);
    }
    else if(device == 2){
        spiDev = open("/dev/spidev1.1", O_RDWR);
    }
    else{
        qDebug() << "ERROR: wrong spidev device chosen! ";
        exit(0);
        //just hope it doesn't happend
    }

    int mode = SPI_MODE0;   //setting SPI mode
    ioctl(spiDev, SPI_IOC_WR_MODE, &mode);

    int lsb_setting = 0;    //0 means MSb first, 1 means LSb first
    ioctl(spiDev, SPI_IOC_WR_LSB_FIRST, &lsb_setting);

    int bits_per_word = 8; // 0 equals default (8)
    ioctl(spiDev, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word);

    struct spi_ioc_transfer xfer;
    memset(&xfer, 0, sizeof(xfer));
    char txbuffer[len];
    char rxbuffer[len];
    txbuffer[0] = 0x01;
    txbuffer[1] = 0x02;
    txbuffer[2] = 0x03;
    txbuffer[3] = 0x04;

    xfer.tx_buf = (unsigned long)txbuffer;
    xfer.rx_buf = (unsigned long)rxbuffer;
    xfer.len = len;
    xfer.speed_hz = 1 * 1000 * 1000;
    xfer.cs_change = 1;
    xfer.bits_per_word = bits_per_word;
    xfer.delay_usecs = 0; //todo: set correct delay
    res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);

    return 0;
}

int connection::getTemp(int device){
    int temp = transfer(device, getTempCmd);
    return (temp - 127);
}

int connection::getHumidity(int device){
    int water = transfer(device, getWaterCmd);
    return water;
}

void connection::setWindow(int device, bool state){
    if(state){
        transfer(device, openWindowCmd);
    }
    else{
        transfer(device, closeWindowCmd);
    }
    return;
}

void connection::setHeater(int device, bool state){
    if(state){
        transfer(device, startHeaterCmd);
    }
    else{
        transfer(device, stopHeaterCmd);
    }
    return;
}

void connection::giveWater(int device){
    transfer(device, addWaterCmd);
    return;
}
