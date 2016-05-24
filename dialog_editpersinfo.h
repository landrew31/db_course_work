#ifndef DIALOG_EDITPERSINFO_H
#define DIALOG_EDITPERSINFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QDebug>
#include "db_setup.h"

#include "ui_dialogui_editpersinfo.h"


namespace Ui {
class DialogUi_editPersInfo;
}

class Dialog_editPersInfo: public QDialog
{
public:
    explicit Dialog_editPersInfo(DB_setup* db = 0, QWidget *parent = 0);
    ~Dialog_editPersInfo();

private:
    Ui::DialogUi_editPersInfo *ui;
    DB_setup *db;

};

#endif // DIALOG_EDITPERSINFO_H
