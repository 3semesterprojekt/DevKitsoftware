#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03


class connection
{
public:
    connection();
    int getTemp();
    int getHumidity();
    void setWindow(bool);
    void setHeater(bool);
    void giveWater();

private:
    int transfer(int, int);

    static const int tempDev = 1;
    static const int waterDev = 2;
    static const int getTempCmd = 0x01;
    static const int getWaterCmd = 0x02;
    static const int openWindowCmd = 0x05;
    static const int closeWindowCmd = 0x06;
    static const int startHeaterCmd = 0x03;
    static const int stopHeaterCmd = 0x04;
    static const int addWaterCmd = 0x07;
};

#endif // CONNECTION_H
