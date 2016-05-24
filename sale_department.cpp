#include "sale_department.h"
#include "dialogentry.h"
#include <QDebug>
#include "renew_sale_table_view_functions.cpp"
#include "renew_sale_combobox_functions.cpp"

Sale_department::Sale_department(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sale_department)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;
    renew_actions(db, ui->tableView_actions);
    renew_contractors(db, ui->tableView_contractors);
    renew_programs(db, ui->tableView_programs);
    renew_cards(db, ui->tableView_cards);
    renew_action_on_program_comboBox(db, ui->action_on_program);
    renew_contr_on_card_comboBox(db, ui->contr_for_card);
    renew_program_on_card_comboBox(db, ui->program_on_card);
    renew_action_on_card_comboBox(db, ui->single_action_on_card);
}

Sale_department::~Sale_department()
{
    delete ui;
}


/* START ACTIONS TAB SLOTS BLOCK */

void Sale_department::on_add_action_button_clicked()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    QString name = ui->action_name_field->text();
    int percent = ui->action_percent_field->text().toInt();
    qDebug() << start << stop << percent;

    db->executeQuery(
                "insert into \"Lupa_A\".actions (day_start, day_stop, action_name, percent) values('"+ start + "','" + stop + "','" + name + "','" + QString::number(percent) + "');",
                "operator",
                this
    );
    renew_actions(db, ui->tableView_actions);

}

void Sale_department::on_tableView_actions_pressed(const QModelIndex &index)
{
    ui->add_action_button->setEnabled(false);
    ui->update_action->setEnabled(true);
    ui->delete_action->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    old_action_name = name;
    qDebug() << old_action_name << endl;
    QDate start = index.sibling(row, 2).data().toDate();
    QString str_start = start.toString();
    QDate stop = index.sibling(row, 3).data().toDate();
    QString str_stop = stop.toString();
    int percent = index.sibling(row, 1).data().toInt();
    QString str_percent = QString::number(percent);
    ui->action_name_field->setText(name);
    ui->action_percent_field->setText(str_percent);
    ui->start_action_date->setDate(start);
    ui->stop_action_date->setDate(stop);
}

void Sale_department::on_update_action_clicked()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    QString name = ui->action_name_field->text();
    int percent = ui->action_percent_field->text().toInt();
    qDebug() << "select update_action('" + old_action_name + "','" + name + "','" + QString::number(percent) + "','" + start + "','" + stop + "');" << endl;
    db->executeQuery(
                "select update_action('" + old_action_name + "','" + name + "','" + QString::number(percent) + "','" + start + "','" + stop + "');",
                "operator",
                this
    );
    renew_actions(db, ui->tableView_actions);
}

void Sale_department::on_clear_action_form_clicked()
{
    ui->action_name_field->clear();
    ui->action_percent_field->clear();
    ui->start_action_date->date();
    ui->stop_action_date->date();
    ui->add_action_button->setEnabled(true);
    ui->update_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
}

void Sale_department::on_delete_action_clicked()
{
    QString name = ui->action_name_field->text();
    db->executeQuery(
                "delete from \"Lupa_A\".actions where action_name = '" + name +"';",
                "operator",
                this
    );
    renew_actions(db, ui->tableView_actions);
}

/* END ACTIONS TAB SLOTS BLOCK */

/* START CONTRACTORS TAB SLOTS BLOCK */

void Sale_department::on_is_individual_clicked(bool checked)
{
    ui->birthday_field->setEnabled(checked);
}

void Sale_department::on_is_entity_clicked(bool checked)
{
    ui->state_number_field->setEnabled(checked);
}

void Sale_department::on_add_contractor_button_clicked()
{
    QString name = ui->contractor_name_field->text();
    QString phone = ui->phone_field->text();
    QString adress = ui->adress_field->text();
    QString birth = "";
    QString number = "";

    if (ui->is_individual->isChecked()) {
        birth = ui->birthday_field->date().toString("yyyy.MM.dd");
    }
    if (ui->is_entity->isChecked()) {
        number = ui->state_number_field->text();
    }
    db->executeQuery(
                "select insert_new_contractor('"+ name + "','" + phone + "','" + adress + "','" + birth + "','" + number + "');",
                "operator",
                this
    );
    renew_contractors(db, ui->tableView_contractors);
    renew_contr_on_card_comboBox(db, ui->contr_for_card);
}

void Sale_department::on_tableView_contractors_pressed(const QModelIndex &index)
{
    ui->add_contractor_button->setEnabled(false);
    ui->update_contractor->setEnabled(true);
    ui->delete_contr->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    old_contr_name = name;
    QString phone = index.sibling(row, 1).data().toString();
    QString adress = index.sibling(row, 2).data().toString();
    QDate birth = index.sibling(row, 3).data().toDate();
    QString str_birth = birth.toString();
    QString numb = index.sibling(row, 4).data().toString();
    ui->contractor_name_field->setText(name);
    ui->phone_field->setText(phone);
    ui->adress_field->setText(adress);
    if (str_birth != "") {
        ui->is_individual->setChecked(true);
        ui->birthday_field->setEnabled(true);
        ui->birthday_field->setDate(birth);
    } else {
        ui->is_individual->setChecked(false);
        ui->birthday_field->setEnabled(false);
        ui->birthday_field->date();
    }
    if (numb != "") {
        ui->is_entity->setChecked(true);
        ui->state_number_field->setEnabled(true);
        ui->state_number_field->setText(numb);
    } else {
        ui->is_entity->setChecked(false);
        ui->state_number_field->setEnabled(false);
        ui->state_number_field->clear();
    }
    qDebug() << name << phone << adress << birth << numb << endl;
}

void Sale_department::on_update_contractor_clicked()
{
    QString name = ui->contractor_name_field->text();
    QString phone = ui->phone_field->text();
    QString adress = ui->adress_field->text();
    QString birth = "";
    QString number = "";

    if (ui->is_individual->isChecked()) {
        birth = ui->birthday_field->date().toString("yyyy.MM.dd");
    }
    if (ui->is_entity->isChecked()) {
        number = ui->state_number_field->text();
    }
    db->executeQuery(
                "select update_contractor('" + old_contr_name + "','" + name + "','" + phone + "','" + adress + "','" + birth + "','" + number + "');",
                "operator",
                this
    );
    renew_contractors(db, ui->tableView_contractors);
}

void Sale_department::on_clear_contr_form_clicked()
{
    ui->contractor_name_field->clear();
    ui->phone_field->clear();
    ui->adress_field->clear();
    ui->is_individual->setChecked(false);
    ui->birthday_field->setEnabled(false);
    ui->birthday_field->date();
    ui->is_entity->setChecked(false);
    ui->state_number_field->setEnabled(false);
    ui->state_number_field->clear();
    ui->add_contractor_button->setEnabled(true);
    ui->update_contractor->setEnabled(false);
    ui->delete_contr->setEnabled(false);
}

void Sale_department::on_delete_contr_clicked()
{
    QString name = ui->contractor_name_field->text();
    db->executeQuery(
                "delete from \"Lupa_A\".contractors where contr_name = '" + name +"';",
                "operator",
                this
    );
    renew_contractors(db, ui->tableView_contractors);
}

/* END CONTRACTORS TAB SLOTS BLOCK */

/* START PROGRAMS TAB SLOTS BLOCK */

void Sale_department::on_add_program_button_clicked()
{
    QString name = ui->program_name_field->text();
    QString action_in_program = ui->action_on_program->currentText();
    db->executeQuery(
                "select insert_new_program('"+ name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs(db, ui->tableView_programs);
}

void Sale_department::on_clear_program_form_clicked()
{
    ui->program_name_field->clear();
    ui->action_on_program->setCurrentIndex(-1);
    ui->add_program_button->setEnabled(true);
    ui->update_program_button->setEnabled(false);
    ui->add_new_action_to_program_button->setEnabled(false);
    ui->delete_action_from_program_button->setEnabled(false);
    ui->delete_program_button->setEnabled(false);
}

void Sale_department::on_tableView_programs_pressed(const QModelIndex &index)
{
    ui->add_program_button->setEnabled(false);
    ui->update_program_button->setEnabled(true);
    ui->add_new_action_to_program_button->setEnabled(true);
    ui->delete_action_from_program_button->setEnabled(true);
    ui->delete_program_button->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    old_program_name = name;
    ui->program_name_field->setText(name);
}

void Sale_department::on_update_program_button_clicked()
{
    QString name = ui->program_name_field->text();

    db->executeQuery(
                "select update_program_name('"+ old_program_name + "','" + name + "');",
                "operator",
                this
    );
    renew_programs(db, ui->tableView_programs);
}

void Sale_department::on_delete_program_button_clicked()
{
    QString name = ui->program_name_field->text();

    db->executeQuery(
                "delete from \"Lupa_A\".action_programs where program_name = '" + name + "';",
                "operator",
                this
    );
    renew_programs(db, ui->tableView_programs);
}

void Sale_department::on_add_new_action_to_program_button_clicked()
{
    QString action_in_program = ui->action_on_program->currentText();

    db->executeQuery(
                "select insert_new_action_in_program('"+ old_program_name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs(db, ui->tableView_programs);
}

void Sale_department::on_delete_action_from_program_button_clicked()
{
    QString action_in_program = ui->action_on_program->currentText();
    db->executeQuery(
                "select delete_action_from_program('"+ old_program_name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs(db, ui->tableView_programs);
}

/* END PROGRAMS TAB SLOTS BLOCK */

/* START CARDS TAB SLOTS BLOCK */

void Sale_department::on_add_card_clicked()
{
    QString contr_name = ui->contr_for_card->currentText();
    QString program = ui->program_on_card->currentText();
    QString action = ui->single_action_on_card->currentText();
    qDebug() << contr_name << program << action << endl;
    qDebug() << "select insert_new_card('" + contr_name + "','" + program + "','" + action + "');" << endl;
    db->executeQuery(
                "select insert_new_card('" + contr_name + "','" + program + "','" + action + "');",
                "operator",
                this
    );
    renew_cards(db, ui->tableView_cards);
}

void Sale_department::on_clear_card_form_clicked()
{
    ui->contr_for_card->setCurrentIndex(-1);
    ui->program_on_card->setCurrentIndex(-1);
    ui->single_action_on_card->setCurrentIndex(-1);
    ui->add_card->setEnabled(true);
    ui->add_program_on_card->setEnabled(false);
    ui->delete_program_from_card->setEnabled(false);
    ui->add_single_action_on_card->setEnabled(false);
    ui->delete_single_action_from_card->setEnabled(false);
}

void Sale_department::on_tableView_cards_pressed(const QModelIndex &index)
{
    ui->add_card->setEnabled(false);
    ui->add_program_on_card->setEnabled(true);
    ui->delete_program_from_card->setEnabled(true);
    ui->add_single_action_on_card->setEnabled(true);
    ui->delete_single_action_from_card->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    ui->contr_for_card->setCurrentIndex(ui->contr_for_card->findText(name));
    old_card_name = name;
}

void Sale_department::on_add_program_on_card_clicked()
{
    QString program_on_card = ui->program_on_card->currentText();

    db->executeQuery(
                "select insert_new_program_on_card('"+ old_card_name + "','" + program_on_card + "');",
                "operator",
                this
    );
    renew_cards(db, ui->tableView_cards);
}

void Sale_department::on_add_single_action_on_card_clicked()
{
    QString action_on_card = ui->single_action_on_card->currentText();

    db->executeQuery(
                "select insert_new_action_on_card('"+ old_card_name + "','" + action_on_card + "');",
                "operator",
                this
    );
    renew_cards(db, ui->tableView_cards);
}

void Sale_department::on_delete_program_from_card_clicked()
{
    QString program_on_card = ui->program_on_card->currentText();

    db->executeQuery(
                "select delete_program_from_card('"+ old_card_name + "','" + program_on_card + "');",
                "operator",
                this
    );
    qDebug() << "select delete_program_from_card('"+ old_card_name + "','" + program_on_card + "');" << endl;
    renew_cards(db, ui->tableView_cards);
}

void Sale_department::on_delete_single_action_from_card_clicked()
{
    QString action_on_card = ui->single_action_on_card->currentText();

    db->executeQuery(
                "select delete_action_from_card('"+ old_card_name + "','" + action_on_card + "');",
                "operator",
                this
    );
    renew_cards(db, ui->tableView_cards);
}
