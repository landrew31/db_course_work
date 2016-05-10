#ifndef DB_SETUP_H
#define DB_SETUP_H

#include <QString>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "messagebox.h"

class DB_setup
{
public:
    DB_setup();
    ~DB_setup();
    bool connect_to_db(QWidget*);
    bool getConnected();
    QString getUser();
    QString getPassword();
    //QSqlDatabase getBase();
    void setUser(QString);
    void setPassword(QString);
    void showMessage(QString, QString);

    QSqlQueryModel* getQueryModel(QString);
    bool executeQuery(QString, QString, QWidget*);

private:
    QSqlDatabase base;
    QString user;
    QString password;
    bool connected;
};

#endif // DB_SETUP_H
