#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>
#include <QVariant>
#include <QDebug>

class MessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = 0);
    void showEvent ( QShowEvent* );
    void timerEvent(QTimerEvent* );
    void setAutoClose(bool);
    void setTimeout(int);

signals:

public slots:

private:
    int timeout;
    int currentTime;
    int autoclose;
    QTimer* timer;
    int left;

};

#endif // MESSAGEBOX_H
