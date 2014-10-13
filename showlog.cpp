#include "showlog.h"
#include "ui_showlog.h"

showLog::showLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showLog)
{
    ui->setupUi(this);
#ifdef __arm__
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
#endif
}

showLog::~showLog()
{
    delete ui;
}

void showLog::on_returnButton_clicked()
{
    this->close();
}

void showLog::init(logFile * ptr){
    ptr_logFile = ptr;
    ui->logViewer->setPlainText("");
    lastEntry = ptr_logFile->getLogNumber();
    for(unsigned int i = 0; i< ptr_logFile->getLogNumber(); i++){
        QTextCursor cursor(ui->logViewer->textCursor());
        cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
        ui->logViewer->setTextCursor(cursor);
        ui->logViewer->insertPlainText(ptr_logFile->getLogEntry(i));
    }
    connect(ptr_logFile, SIGNAL(logFileUpdated()), this, SLOT(update()));
}

void showLog::update(){
    while(lastEntry < ptr_logFile->getLogNumber()){
        QTextCursor cursor(ui->logViewer->textCursor());
        cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
        ui->logViewer->setTextCursor(cursor);
        ui->logViewer->insertPlainText(ptr_logFile->getLogEntry(lastEntry));
        lastEntry++;
    }

}

void showLog::on_clearLog_clicked()
{
    ptr_logFile->clearLog();
    lastEntry = 0;
    ui->logViewer->clear();
    QTextCursor cursor(ui->logViewer->textCursor());
    cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
}
