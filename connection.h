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
    int gettemp();
    int getwater();
    void setwindow(bool);
    void setheater(bool);
    void givewater();

private:
    int transfer(int, int);

    static const int tempdev = 1;
    static const int waterdev = 2;
    static const int gettempcmd = 0x01;
    static const int getwatercmd = 0x02;
    static const int openwindowcmd = 0x05;
    static const int closewindowcmd = 0x06;
    static const int startheatercmd = 0x03;
    static const int stopheatercmd = 0x04;
    static const int addwatercmd = 0x07;
};

#endif // CONNECTION_H
