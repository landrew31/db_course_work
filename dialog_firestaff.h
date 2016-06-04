#ifndef DIALOG_FIRESTAFF_H
#define DIALOG_FIRESTAFF_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_fireStaff;
}

class Dialog_fireStaff : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fireStaff(DB_setup* db = 0, int selectedStaffId = 0, int selectedPersId = 0, QWidget *parent = 0);
    ~Dialog_fireStaff();

private slots:
    void showInpValues();
    void accept();

private:
    Ui::Dialog_fireStaff *ui;
    DB_setup* db;
    int staffId, persId;
};

#endif // DIALOG_FIRESTAFF_H
