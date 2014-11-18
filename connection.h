#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <vector>

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03


class connection
{
public:
    connection();
    int getTemp();
    int getOutTemp();
    int getHumidity();
    void getValues(int device);
    void setWindow(int device, bool state);
    void setHeater(int device, bool state);
    void giveWater(int device);

private:
    char txbuffer[4];
    char rxbuffer[4];
    int temp;
    int humidity;
    int outTemp;
    std::vector<bool> heater;
    std::vector<bool> window;
    std::vector<bool> water;
};
#endif // CONNECTION_H
