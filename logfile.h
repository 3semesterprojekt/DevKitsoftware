#ifndef LOGFILE_H
#define LOGFILE_H
#include <QString>
#include <vector>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QObject>

class logFile : public QObject
{
    Q_OBJECT
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
signals:
    void logFileUpdated(void);
};

#endif // LOGFILE_H
