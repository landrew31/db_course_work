#ifndef DIALOG_EDITPERSINFO_H
#define DIALOG_EDITPERSINFO_H

#include <QDialog>

#include "hr_department.h"
#include "dialog_createskill.h"
#include "ui_dialogui_editpersinfo.h"


namespace Ui {
class DialogUi_editPersInfo;
}

class Dialog_editPersInfo: public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_editPersInfo(DB_setup* db = 0, QString selectedStaffId = "", QWidget *parent = 0);
    ~Dialog_editPersInfo();

private slots:
    void accept();
    void on_button_addSkill_clicked();
    void on_button_createSkill_clicked();
    void showInpValues();
    void removeSkill();

private:
    Ui::DialogUi_editPersInfo *ui;
    DB_setup *db;
    int persId;
    QSqlQueryModel* modelAllSkills;
};

#endif // DIALOG_EDITPERSINFO_H
