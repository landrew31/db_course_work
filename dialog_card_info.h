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
#include "dialog_contractors.h"
#include "dialog_program_info.h"

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

    static void renew_contr_programs(DB_setup* db, QString contr, QTableView* table);
    static void renew_program_on_card_comboBox(DB_setup* db, QComboBox* box);
    ~Dialog_card_info();

private slots:
    void on_update_contr_clicked();


    void on_add_new_program_clicked();

    void on_tableView_contr_programs_pressed(const QModelIndex &index);

    void on_add_program_on_card_clicked();

    void on_clear_program_buffer_clicked();

    void on_update_program_button_clicked();

    void on_action_on_program_info_clicked();

    void on_delete_program_button_clicked();

private:
    Ui::Dialog_card_info *ui;
    DB_setup *db;
    QTableView *table_contr;
    QTableView *table_programs;
    QTableView *table_actions;
    QString *contr_data;
    QString *old_program_data = new QString[3];
};

#endif // DIALOG_CARD_INFO_H
