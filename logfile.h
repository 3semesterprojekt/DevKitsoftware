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
    unsigned int getLogNumber();
    QString getLogEntry(unsigned int);
    void setLogEvent(QString);
    bool saveToFile();
    void clearLog();
private:
    QString getTimestamp(bool mode);
    std::vector<QString> eventLog;
};

#endif // LOGFILE_H
