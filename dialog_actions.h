#ifndef DIALOG_ACTIONS_H
#define DIALOG_ACTIONS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include "db_setup.h"

#include "ui_dialog_actions.h"

namespace Ui {
class Dialog_actions;
}

class Dialog_actions : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_actions(DB_setup* db=0, QWidget *parent = 0);
    ~Dialog_actions();

private:
    Ui::Dialog_actions *ui;
    DB_setup *db;
};

#endif // DIALOG_ACTIONS_H
