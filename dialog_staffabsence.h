#ifndef DIALOG_STAFFABSENCE_H
#define DIALOG_STAFFABSENCE_H

#include <QDialog>
#include "hr_department.h"
#include "dialog_addstaffabsence.h"

namespace Ui {
class Dialog_staffabsence;
}

class Dialog_staffabsence : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_staffabsence(DB_setup* db = 0, int selectedStaffId = 0, QWidget *parent = 0);
    ~Dialog_staffabsence();

private slots:
    void showInpValues();

    void on_addAbsence_clicked();

private:
    Ui::Dialog_staffabsence *ui;
    DB_setup* db;
    int staffId;
};

#endif // DIALOG_STAFFABSENCE_H
