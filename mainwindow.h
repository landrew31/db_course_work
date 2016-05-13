#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include "db_setup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DB_setup *db = 0, QWidget *parent = 0);
    void renew_actions();
    void renew_contractors();
    void renew_programs();
    void renew_cards();
    void renew_action_on_program_comboBox();
    void renew_contr_on_card_comboBox();
    void renew_program_on_card_comboBox();
    void renew_action_on_card_comboBox();

    void renew_persons();
    ~MainWindow();

private slots:
    void on_add_action_button_clicked();

    void on_is_individual_clicked(bool checked);

    void on_is_entity_clicked(bool checked);

    void on_add_contractor_button_clicked();


    void on_tableView_contractors_pressed(const QModelIndex &index);

    void on_clear_contr_form_clicked();

    void on_delete_contr_clicked();

    void on_tableView_actions_pressed(const QModelIndex &index);

    void on_clear_action_form_clicked();

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

private:
    Ui::MainWindow *ui;
    DB_setup *db;
    QString old_action_name;
    QString old_contr_name;
    QString old_program_name;
    QString old_card_name;
};

#endif // MAINWINDOW_H
