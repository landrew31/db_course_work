#ifndef DIALOG_PROGRAM_INFO_H
#define DIALOG_PROGRAM_INFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"
#include "dialog_actions.h"
#include "dialog_programs.h"

#include "ui_dialog_program_info.h"

namespace Ui {
class Dialog_program_info;
}

class Dialog_program_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_program_info(DB_setup* db=0,
                                 QTableView *table_programs=0,
                                 QTableView *table_actions=0,
                                 QString* program_data = 0,
                                 QWidget *parent = 0);
    static void renew_program_actions(DB_setup* db, QString program, QTableView* table);
    static void renew_action_on_card_comboBox(DB_setup* db, QComboBox* box);
    ~Dialog_program_info();



private slots:
    void on_update_program_clicked();

    void on_add_new_action_clicked();

    void on_add_action_to_program_clicked();

    void on_tableView_program_actions_pressed(const QModelIndex &index);

    void on_clear_action_buffer_clicked();

    void on_update_action_clicked();

    void on_delete_action_clicked();

private:
    Ui::Dialog_program_info *ui;
    DB_setup* db;
    QTableView *table_programs;
    QTableView *table_actions;
    QString *program_data;
    QString *old_action_data; //= new QString[4];
};

#endif // DIALOG_PROGRAM_INFO_H
