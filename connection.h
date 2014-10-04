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
    unsigned long transfer(int, unsigned long);
    int convert(unsigned long);

    static const int tempdev = 1;
    static const int waterdev = 2;
    static const unsigned long gettempcmd = 0;
    static const unsigned long getwatercmd = 0;
    static const unsigned long openwindowcmd = 0;
    static const unsigned long closewindowcmd = 0;
    static const unsigned long startheatercmd = 0;
    static const unsigned long stopheatercmd = 0;
    static const unsigned long changewatercmd = 0;
};

#endif // CONNECTION_H
