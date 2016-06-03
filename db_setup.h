#ifndef DB_SETUP_H
#define DB_SETUP_H

#include <QString>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QTableView>
#include <QHeaderView>

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
    void setUser(QString);
    void setPassword(QString);
    void showMessage(QString, QString);
    void showExecutionResultStatus(int);
    QSqlQueryModel* getQueryModel(QString);
    bool executeQuery(QString, QString, QWidget*, int);
    static void table_column_entire_width(QTableView *table);

private:
    QSqlDatabase base;
    QString user;
    QString password;
    bool connected;
};

#endif // DB_SETUP_H
