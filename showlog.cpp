#include "showlog.h"
#include "ui_showlog.h"

showlog::showlog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showlog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);   //hide title bar
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(500);
}

showlog::~showlog()
{
    delete ui;
}

void showlog::on_return_2_clicked()
{
    this->close();
}

void showlog::init(logfile * ptr){
    ptr_logfile = ptr;
    ui->logviewer->setPlainText("");
    for(unsigned int i = 0; i< ptr_logfile->getlognumber(); i++){
        QTextCursor cursor(ui->logviewer->textCursor());
        cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
        ui->logviewer->setTextCursor(cursor);
        ui->logviewer->insertPlainText(ptr_logfile->getlogentry(i));
    }
}

void showlog::update(){
    //code to update and redraw any new log entries

}
