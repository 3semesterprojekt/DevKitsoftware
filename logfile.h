#ifndef LOGFILE_H
#define LOGFILE_H
#include <QString>
#include <vector>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class logFile
{
public:
    logFile();
    unsigned int getLogNumber();
    QString getLogEntry(unsigned int number);
    void setLogEvent(QString logString);
    bool saveToFile();
    void clearLog();

private:
    QString getTimestamp(bool mode);
    std::vector<QString> eventLog;
};

#endif // LOGFILE_H
