#ifndef DIALOG_GOOD_ACTIONS_INFO_H
#define DIALOG_GOOD_ACTIONS_INFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"
#include "dialog_actions.h"
#include "dialog_good_types.h"

#include "ui_dialog_good_actions_info.h"

namespace Ui {
class Dialog_good_actions_info;
}

class Dialog_good_actions_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_good_actions_info(DB_setup *db=0,
                                      QTableView *table_goods=0,
                                      QTableView *table_actions=0,
                                      QString* good_data=0,
                                      QWidget *parent = 0);
    void renew_good_actions(DB_setup* db, QString good, QTableView* table );

    ~Dialog_good_actions_info();

private slots:
    void renew_actions_comboBox();

    void on_tableView_actions_good_pressed(const QModelIndex &index);

    void on_update_good_type_clicked();

    void on_add_new_action_clicked();

    void on_add_action_to_good_clicked();

    void on_clear_action_buffer_clicked();

    void on_update_action_clicked();

    void on_delete_action_clicked();

private:
    Ui::Dialog_good_actions_info *ui;
    DB_setup *db;
    QTableView *table_goods;
    QTableView *table_actions;
    QString *good_data;
    QString *old_action_data;
};

#endif // DIALOG_GOOD_ACTIONS_INFO_H
