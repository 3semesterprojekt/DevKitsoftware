#include "connection.h"
#include <QDebug>

connection::connection()
{
}


int connection::transfer(int device, int cmd){

    int res = 0;
    int spiDev;
    int len = 1;
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
    switch(cmd){
    case 1: txbuffer[0] = 0x01; //gettemp
        break;
    case 2: txbuffer[0] = 0x02; //getwater
        break;
    case 3: txbuffer[0] = 0x03; //turn on heater
        break;
    case 4: txbuffer[0] = 0x04; //turn off heater
        break;
    case 5: txbuffer[0] = 0x05; //open window
        break;
    case 6: txbuffer[0] = 0x06; //close window
        break;
    case 7: txbuffer[0] = 0x07; //water plant
        break;
    default: txbuffer[0] = 0x00;

        break;
    }
    xfer.tx_buf = (unsigned long)txbuffer;
    xfer.rx_buf = (unsigned long)rxbuffer;
    xfer.len = len;
    xfer.speed_hz = 1 * 1000 * 1000;
    xfer.cs_change = 1;
    xfer.bits_per_word = bits_per_word;
    xfer.delay_usecs = 0; //todo: set correct delay
    res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);
    qDebug() << (int)rxbuffer[0];

    if(res == len){
        return (int)rxbuffer[0];
    }
    else{
        return -1;
    }
}

int connection::gettemp(){
    int temp = transfer(tempdev, gettempcmd);
    return (temp - 127);
}

int connection::getwater(){
    int water = transfer(waterdev, getwatercmd);
    return water;
}

void connection::setwindow(bool state){
    if(state){
        transfer(tempdev, openwindowcmd);
    }
    else{
        transfer(tempdev, closewindowcmd);
    }
    return;
}

void connection::setheater(bool state){
    if(state){
        transfer(tempdev, startheatercmd);
    }
    else{
        transfer(tempdev, stopheatercmd);
    }
    return;
}

void connection::givewater(){
    transfer(waterdev, addwatercmd);
    return;
}
