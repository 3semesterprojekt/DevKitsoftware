#include "connection.h"

connection::connection()
{
}


unsigned long connection::transfer(int device, unsigned long tx){

    int res;
    int spiDev;
    int mode = SPI_MODE0;
    int lsb_setting = 0; //0 means MSb first, 1 means LSb fist
    int bits_per_word = 8;
    unsigned long rx;
    struct spi_ioc_transfer xfer;

    if(device == 1){
        spiDev = open("/dev/spidev1.0", O_RDWR);
    }
    if(device == 2){
        spiDev = open("/dev/spidev1.1", O_RDWR);
    }
    ioctl(spiDev, SPI_IOC_WR_MODE, &mode); //set mode
    ioctl(spiDev, SPI_IOC_WR_LSB_FIRST, &lsb_setting);
    ioctl(spiDev, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word);
    memset(&xfer, 0, sizeof(xfer));

    xfer.tx_buf = tx;
    xfer.rx_buf = rx;
    xfer.len = sizeof(unsigned long);
    xfer.speed_hz =  1 * 1000 * 1000;
    xfer.cs_change = 1;
    xfer.bits_per_word = bits_per_word;
    xfer.delay_usecs = 0;

    //res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);

    return rx;

}

int connection::gettemp(){
    unsigned long longtemp;
    longtemp = transfer(tempdev, gettempcmd);
    int temp = convert(longtemp);
    return temp;
}

int connection::getwater(){
    unsigned long longwater;
    longwater = transfer(waterdev, getwatercmd);
    int water = convert(longwater);
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
    transfer(waterdev, changewatercmd);
    return;
}

int connection::convert(unsigned long input){
    int output = 0;


    return output;
}
