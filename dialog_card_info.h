#ifndef DIALOG_CARD_INFO_H
#define DIALOG_CARD_INFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"
#include "dialog_programs.h"

#include "ui_dialog_card_info.h"

namespace Ui {
class Dialog_card_info;
}

class Dialog_card_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_card_info(DB_setup* db=0,
                              QTableView *table_contr=0,
                              QTableView *table_programs=0,
                              QTableView *table_actions=0,
                              QString* contr_data = 0,
                              QWidget *parent = 0);
    ~Dialog_card_info();

private:
    Ui::Dialog_card_info *ui;
    QTableView *table_contr;
    QTableView *table_programs;
    QTableView *table_actions;
    QString *contr_data;
    QString *old_program_data = new QString[3];
};

#endif // DIALOG_CARD_INFO_H
