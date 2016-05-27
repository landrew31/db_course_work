#ifndef DIALOG_EDITPERSINFO_H
#define DIALOG_EDITPERSINFO_H

#include <QDialog>
#include "db_setup.h"

#include "hr_department.h"
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
    void showInpValues();

private slots:
    void accept();
    void on_button_addSkill_clicked();

private:
    Ui::DialogUi_editPersInfo *ui;
    DB_setup *db;
    QString persId;
    QString selectedNewSkillId;
    QString searchSkillIdByNameInModel(QString);
    QSqlQueryModel* modelAllSkills;
};

#endif // DIALOG_EDITPERSINFO_H
