#include "connection.h"
#include <QDebug>

connection::connection()
{
    temp = 0;
    humidity = 0;
    heater.assign(2,false);
    window.assign(2,false);
    water.assign(2,false);

}

void connection::init(Database* ptr){
    ptr_database = ptr;
}

void connection::getValues(int device){
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
    txbuffer[0] = (heater.at(device)?0xAA:0x00);
    txbuffer[1] = (window.at(device)?0xAA:0x00);
    txbuffer[2] = (water.at(device)?0xAA:0x00);
    txbuffer[3] = txbuffer[0] ^ txbuffer[1] ^ txbuffer[2];

    qDebug() << "heater: " <<(unsigned int)txbuffer[0];
    qDebug() << "window: " <<(unsigned int)txbuffer[1];
    qDebug() << "water: " << (unsigned int)txbuffer[2];

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
    xfer.speed_hz = 100 * 1000; //100 KHz
    xfer.cs_change = 0;
    xfer.bits_per_word = bits_per_word;
    xfer.delay_usecs = 150; //todo: set correct delay
    res = ioctl(spiDev, SPI_IOC_MESSAGE(1), &xfer);

    if((rxbuffer[0] ^ rxbuffer[1] ^ rxbuffer[2]) == rxbuffer[3]){
        humidity = (unsigned int) rxbuffer[0];
        if((unsigned int) rxbuffer[2] < 128){
            temp = (unsigned int) rxbuffer[2];
        }
        else{
            temp = ((unsigned int) rxbuffer[2]) -255;
        }
        if((unsigned int) rxbuffer[1] < 128){
            outTemp = (unsigned int) rxbuffer[1];
        }
        else{
            outTemp = ((unsigned int) rxbuffer[1]) -255;
        }

        qDebug() << "temp: " << temp;
        qDebug() << "humidity: " << humidity;
        qDebug() << "outTemp: " << outTemp;
        qDebug() << "checksum" << (unsigned int)rxbuffer[3];
        qDebug() << "-------------------------";

        ptr_database->WriteMeasurementRow(1,humidity);
        ptr_database->WriteMeasurementRow(2,temp);
        ptr_database->WriteMeasurementRow(3,outTemp);
        ptr_database->WriteSensorRow("Humidity",humidity,1);
        ptr_database->WriteSensorRow("IndoorTemp",temp,2);
        ptr_database->WriteSensorRow("OutdoorTemp",outTemp,3);


    }
    else{
        qDebug() << "temp: " << (unsigned int) rxbuffer[2];
        qDebug() << "humidity: " << (unsigned int) rxbuffer[0];
        qDebug() << "outTemp: " << (unsigned int) rxbuffer[1];
        qDebug() << "checksum" << (unsigned int)rxbuffer[3];
        qDebug() << "SPI DATA FAIL!";
        qDebug() << "-------------------------";
    }
    water.at(device) = false;
    return;
}

int connection::getTemp(){
    return temp;
}

int connection::getOutTemp(){
    return outTemp;
}

int connection::getHumidity(){
    return humidity;
}

void connection::setWindow(int device, bool state){
    window.at(device) = state;
    return;
}

void connection::setHeater(int device, bool state){
    heater.at(device) = state;
    return;
}

void connection::giveWater(int device){
    water.at(device) = true;
    return;
}
