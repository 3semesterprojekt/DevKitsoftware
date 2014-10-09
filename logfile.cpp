#include "logfile.h"

logfile::logfile(){
}

QString logfile::getLogEntry(unsigned int number){
    if(eventLog.size()>number){
        return eventLog.at(number);
    }
    else{
        return "ERROR";
    }
}

unsigned int logfile::getLogNumber(){
    return eventLog.size();
}

void logfile::setLogEvent(QString string){
    QString tmp = "";
//  tmp.append("[");
//  tmp.append(gettimestamp(true));
//  tmp.append("]");
    tmp.append(string);
    tmp.append("\n");
    if(eventLog.size() < eventLog.max_size()){
        eventLog.push_back(tmp);
    }
    else{
        saveToFile();
        clearLog();
        eventLog.push_back(tmp);
    }
    return;
}

QString logfile::getTimestamp(bool mode){ //mode = false gives date while mode = true gives datetime
    QDateTime tmp;
    if(mode){
        return tmp.currentDateTime().toString();
    }
    else{
        return tmp.date().toString();
    }
}

bool logfile::saveToFile(){
    QString filename = "logfiles/logfile";
    filename.append(getTimestamp(false));
    filename.append(".txt");
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);


        stream << "This is the automaticly createt greenhouse logfile" << endl;
        stream << "##################################################" << endl;
        for(unsigned int i = 0; i < eventLog.size(); i++){

            stream << eventLog.at(i) << endl;
        }
        file.close();
        return true;
    }

    else{
        return false;
    }
}

void logfile::clearLog(){
    eventLog.clear();
}
