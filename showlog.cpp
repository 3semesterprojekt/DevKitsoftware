#include "showlog.h"
#include "ui_showlog.h"

showLog::showLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showLog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000); //updated every second
}

showLog::~showLog()
{
    delete ui;
}

void showLog::on_return_clicked()
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
