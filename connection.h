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
    void getValues(int device);
    void setWindow(int device, bool state);
    void setHeater(int device, bool state);
    void giveWater(int device);

private:
    int transfer(int deviceID, int command);
    char txbuffer[4];
    char rxbuffer[4];
    int temp;
    int humidity;

    enum SPICommands{
        NOTHING = 0,
        OPENWINDOW = 1,
        CLOSEWINDOW = 2,
        STARTHEATER = 3,
        STOPHEATER = 4,
        ADDWATER = 5
    };
};

#endif // CONNECTION_H
