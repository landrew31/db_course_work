#ifndef DIALOG_EDITPOSITION_H
#define DIALOG_EDITPOSITION_H

#include <QDialog>

#include "hr_department.h"
#include "dialog_createskill.h"
#include "ui_dialog_editposition.h"


namespace Ui {
class Dialog_editPosition;
}

class Dialog_editPosition : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_editPosition(DB_setup* db = 0, int selectedPositId = 0, QWidget *parent = 0);
    ~Dialog_editPosition();

private slots:
    void accept();
    void on_button_addSkill_clicked();
    void on_button_createSkill_clicked();
    void showInpValues();
    void removeSkill();

private:
    Ui::Dialog_editPosition *ui;
    DB_setup *db;
    int positId;
    QSqlQueryModel* modelAllSkills;
    QVector<int> skills;

    void inserSkillIntoList(QString, int);
};

#endif // DIALOG_EDITPOSITION_H
