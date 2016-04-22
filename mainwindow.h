#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDateEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool enterDB();
    void setDB(QString user, QString password);
    ~MainWindow();

private slots:
    void on_renew_actions_button_clicked();

    void on_add_action_button_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString user;
    QString password;
};

#endif // MAINWINDOW_H
