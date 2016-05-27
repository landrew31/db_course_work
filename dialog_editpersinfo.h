#ifndef DIALOG_EDITPERSINFO_H
#define DIALOG_EDITPERSINFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QVector>
#include <QLayoutItem>
#include <QModelIndex>
#include <QDebug>
#include "db_setup.h"

#include "hr_department.h"

#include "ui_dialogui_editpersinfo.h"


namespace Ui {
class DialogUi_editPersInfo;
}

class Dialog_editPersInfo: public QDialog
{
public:
    explicit Dialog_editPersInfo(DB_setup* db = 0, QString selectedStaffId = "", QWidget *parent = 0);
    ~Dialog_editPersInfo();

    void showInpValues();

private slots:
    void accept();

private:
    Ui::DialogUi_editPersInfo *ui;
    DB_setup *db;
    QString persId;

};

#endif // DIALOG_EDITPERSINFO_H
