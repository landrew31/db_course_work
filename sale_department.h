#ifndef SALE_DEPARTMENT_H
#define SALE_DEPARTMENT_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include "db_setup.h"


#include "ui_sale_department.h"
#include "ui_dialog_actions.h"

#include "dialog_actions.h"
#include "dialog_contractors.h"
#include "dialog_programs.h"
#include "dialog_program_info.h"
#include "dialog_card_info.h"
#include "dialog_doc_types.h"
#include "dialog_good_types.h"
#include "dialog_good_actions_info.h"
#include "dialog_buy_goods.h"

namespace Ui {
class Sale_department;
}

class Sale_department : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sale_department(DB_setup *db = 0, QWidget *parent = 0);
    ~Sale_department();

private slots:
    /* add slots */

    void on_add_action_button_clicked();
    void on_add_contractor_button_clicked();
    void on_add_program_button_clicked();    
    void on_add_new_doc_type_clicked();
    void on_add_new_good_type_clicked();

    /* pressed tableView slots */

    void on_tableView_contractors_pressed(const QModelIndex &index);    
    void on_tableView_actions_pressed(const QModelIndex &index);
    void on_tableView_programs_pressed(const QModelIndex &index);
    void on_tableView_doc_types_pressed(const QModelIndex &index);
    void on_tableView_good_types_pressed(const QModelIndex &index);

    /* update slots */

    void on_update_action_clicked();
    void on_update_contractor_clicked();
    void on_update_program_button_clicked();
    void on_update_doc_type_clicked();
    void on_update_good_type_clicked();


    /* delete slots */

    void on_delete_contr_clicked();
    void on_delete_action_clicked();
    void on_delete_program_button_clicked();
    void on_delete_doc_type_clicked();
    void on_delete_good_type_clicked();


    /* clear buffer slots */

    void on_clear_action_buffer_clicked();
    void on_clear_contractor_buffer_clicked();
    void on_clear_program_buffer_clicked();
    void on_clear_doc_type_buffer_clicked();
    void on_clear_good_type_buffer_clicked();


    /* addition info slots */
    void on_action_on_program_info_clicked();
    void on_card_info_clicked();
    void on_action_on_good_info_clicked();



    void on_buy_goods_clicked();
    void renew_documents();
    void renew_left_goods();

    void on_see_goods_left_clicked();

    void on_see_docs_clicked();

    void on_clear_doc_buffer_clicked();

    void on_tableView_moves_pressed(const QModelIndex &index);

    void on_sale_goods_clicked();

private:
    Ui::Sale_department *ui;
    DB_setup *db;
    QString old_action_data[4];
    QString old_contr_data[5];
    QString old_program_data[3];
    QString old_doc_type_data;
    QString old_good_data[4];
    QString old_doc;
};

#endif // SALE_DEPARTMENT_H
