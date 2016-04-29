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
#include <QModelIndex>

#include "db_setup.h"
#include "contractors.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DB_setup *db = 0, QWidget *parent = 0);
    void renew_actions();
    void renew_contractors();
    ~MainWindow();

private slots:
    void on_add_action_button_clicked();

    void on_is_individual_clicked(bool checked);

    void on_is_entity_clicked(bool checked);

    void on_add_contractor_button_clicked();


    void on_tableView_contractors_pressed(const QModelIndex &index);

    void on_clear_contr_form_clicked();

    void on_delete_contr_clicked();

private:
    Ui::MainWindow *ui;
    DB_setup *db;
};

#endif // MAINWINDOW_H
