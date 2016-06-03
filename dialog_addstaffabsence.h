#ifndef DIALOG_ADDSTAFFABSENCE_H
#define DIALOG_ADDSTAFFABSENCE_H

#include <QDialog>
#include "hr_department.h"
#include "dialog_createabstype.h"

namespace Ui {
class Dialog_addStaffAbsence;
}

class Dialog_addStaffAbsence : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_addStaffAbsence(DB_setup* db = 0, int selectedStaffId = 0, QWidget *parent = 0);
    ~Dialog_addStaffAbsence();

private slots:
    void showInpValues();
    void on_createAbsType_clicked();
    void accept();

private:
    Ui::Dialog_addStaffAbsence *ui;
    DB_setup* db;
    QSqlQueryModel* allAbsTypes;
    int staffId;
};

#endif // DIALOG_ADDSTAFFABSENCE_H
