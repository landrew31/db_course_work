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
    void on_add_action_button_clicked();



    void on_add_contractor_button_clicked();


    void on_tableView_contractors_pressed(const QModelIndex &index);


    void on_delete_contr_clicked();

    void on_tableView_actions_pressed(const QModelIndex &index);



    void on_delete_action_clicked();

    void on_update_action_clicked();

    void on_update_contractor_clicked();

    void on_add_program_button_clicked();

    void on_clear_program_form_clicked();

    void on_tableView_programs_pressed(const QModelIndex &index);

    void on_update_program_button_clicked();

    void on_delete_program_button_clicked();

    void on_add_new_action_to_program_button_clicked();

    void on_delete_action_from_program_button_clicked();

    void on_add_card_clicked();

    void on_clear_card_form_clicked();

    void on_tableView_cards_pressed(const QModelIndex &index);

    void on_add_program_on_card_clicked();

    void on_add_single_action_on_card_clicked();

    void on_delete_program_from_card_clicked();

    void on_delete_single_action_from_card_clicked();

    void on_clear_action_buffer_clicked();

    void on_clear_contractor_buffer_clicked();

private:
    Ui::Sale_department *ui;
    DB_setup *db;
    QString old_action_data[4];
    QString old_contr_data[5];
    QString old_program_name;
    QString old_card_name;
};

#endif // SALE_DEPARTMENT_H
