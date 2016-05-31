#ifndef DIALOG_REMOVEVACANCY_H
#define DIALOG_REMOVEVACANCY_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_removeVacancy;
}

class Dialog_removeVacancy : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_removeVacancy(DB_setup* db = 0, int selectedPositId = 0, QString positName = "", QWidget *parent = 0);
    ~Dialog_removeVacancy();

private slots:
    void accept();

private:
    Ui::Dialog_removeVacancy *ui;
    DB_setup *db;
    int positId;
    QString positName;
};

#endif // DIALOG_REMOVEVACANCY_H
