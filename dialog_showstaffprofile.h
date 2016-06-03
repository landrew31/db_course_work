#ifndef DIALOG_SHOWSTAFFPROFILE_H
#define DIALOG_SHOWSTAFFPROFILE_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_showStaffProfile;
}

class Dialog_showStaffProfile : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_showStaffProfile(DB_setup* db = 0, int selectedPersId = 0, QWidget *parent = 0);
    ~Dialog_showStaffProfile();

private slots:
    void showInpValues();

private:
    Ui::Dialog_showStaffProfile *ui;
    DB_setup* db;
    int persId;
};

#endif // DIALOG_SHOWSTAFFPROFILE_H
