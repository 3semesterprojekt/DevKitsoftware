#ifndef CONNECTION_H
#define CONNECTION_H

/* tom classe som skal indeholde funktionalitet til at oprette
 * en SPI forbindelse til PSOC
 * of indeholder funktioner til nemt at sende og modtage data
 * over disse forbindelser.
 */

class connection
{
public:
    connection();
    int gettemp();
    int getwater();
    void setheater(bool);
    void setwindow(bool);
    void outwater(int);

private:
    /*
     * write function
     * reade function
     * setup fuction
     * connectionhandler/connectionide variables
    */
};

#endif // CONNECTION_H
