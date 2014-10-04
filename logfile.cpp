#include "logfile.h"

logfile::logfile(){
}

QString logfile::getlogentry(unsigned int number){
    if(eventlog.size()>number){
        return eventlog.at(number);
    }
    else{
        return "ERROR";
    }
}

unsigned int logfile::getlognumber(){
    return eventlog.size();
}

void logfile::setlogevent(QString string){
    QString tmp = "";
//  tmp.append("[");
//  tmp.append(gettimestamp(true));
//  tmp.append("]");
    tmp.append(string);
    tmp.append("\n");
    if(eventlog.size() < eventlog.max_size()){
        eventlog.push_back(tmp);
    }
    else{
        savetofile();
        clearlog();
        eventlog.push_back(tmp);
    }
    return;
}

QString logfile::gettimestamp(bool mode){ //mode = false gives date while mode = true gives datetime
    QDateTime tmp;
    if(mode){
        return tmp.currentDateTime().toString();
    }
    else{
        return tmp.date().toString();
    }
}

bool logfile::savetofile(){
    QString filename = "logfiles/logfile";
    filename.append(gettimestamp(false));
    filename.append(".txt");
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);


        stream << "This is the automaticly createt greenhouse logfile" << endl;
        stream << "##################################################" << endl;
        for(unsigned int i = 0; i < eventlog.size(); i++){

            stream << eventlog.at(i) << endl;
        }
        file.close();
        return true;
    }

    else{
        return false;
    }
}

void logfile::clearlog(){
    eventlog.clear();
}
