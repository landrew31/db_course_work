#ifndef HR_DEPARTMENT_H
#define HR_DEPARTMENT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QDebug>
#include "db_setup.h"

#include "ui_hr_department.h"

#include "dialog_editpersinfo.h"


namespace Ui {
class HR_department;
}

class HR_department : public QMainWindow
{
    Q_OBJECT

public:
    explicit HR_department(DB_setup *db = 0, QWidget *parent = 0);
    ~HR_department();

    void showStaffTable();

private slots:

    void on_button_closeWindow_clicked();

    void on_button_editPersInfo_clicked();

    void on_table_staff_pressed(const QModelIndex &index);

    void on_date_historyView_dateChanged();

private:
    Ui::HR_department *ui;
    DB_setup *db;
};

#endif // HR_DEPARTMENT_H
