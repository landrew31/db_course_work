#include "messagebox.h"

MessageBox::MessageBox(QWidget *parent) :
    QMessageBox(parent)
{
    timer =new QTimer(this);
    this->setButtonText(QMessageBox::Ok, "OK (До закриття: " + QString::number(left) + "с");
}


void MessageBox::showEvent ( QShowEvent * event ) {
    currentTime = 0;
    this->startTimer(1000);
}

void MessageBox::timerEvent(QTimerEvent *event)
{
    currentTime++;
    left = timeout - currentTime;
    this->setButtonText(QMessageBox::Ok, "OK (До закриття: " + QString::number(left) + " с)");
//    qDebug() << timeout - currentTime << endl;
    if (currentTime>=timeout) {
    this->done(0);
    }
}


void MessageBox::setAutoClose( bool autoclo ) {
    autoclose = autoclo;
}


void MessageBox::setTimeout(int time)
{
    timeout = time;
}
