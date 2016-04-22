#ifndef DIALOGENTRY_H
#define DIALOGENTRY_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>

#include "mainwindow.h"

namespace Ui {
class DialogEntry;
}

class DialogEntry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEntry(QWidget *parent = 0);
    bool connect_to_db();
    bool getConnected();
    ~DialogEntry();

private slots:
    void on_username_field_textChanged(const QString &arg1);

    void on_password_field_textChanged(const QString &arg1);

    void on_cancel_entry_button_clicked();

    void on_enter_button_clicked();

private:
    Ui::DialogEntry *ui;
    QString user;
    QString password;
    bool connected = false;
    QSqlDatabase db;
};

#endif // DIALOGENTRY_H
