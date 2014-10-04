#ifndef LOGFILE_H
#define LOGFILE_H
#include <QString>
#include <vector>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class logfile
{
public:
    logfile();
    unsigned int getlognumber();
    QString getlogentry(unsigned int);
    void setlogevent(QString);
    bool savetofile();
    void clearlog();
private:
    QString gettimestamp(bool);
    std::vector<QString> eventlog;
};

#endif // LOGFILE_H
