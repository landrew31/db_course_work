#ifndef HR_DEPARTMENT_H
#define HR_DEPARTMENT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include "db_setup.h"


namespace Ui {
class HR_department;
}

class HR_department : public QMainWindow
{
    Q_OBJECT

public:
    explicit HR_department(DB_setup *db = 0, QWidget *parent = 0);
    void renewPersons();

    ~HR_department();

private slots:

    void on_button_closeWindow_clicked();

private:
    Ui::HR_department *ui;
    DB_setup *db;
};

#endif // HR_DEPARTMENT_H
