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
    Dialog_actions::renew_actions(db, ui->tableView_actions);
    Dialog_contractors::renew_contractors(db, ui->tableView_contractors);
    Dialog_programs::renew_programs(db, ui->tableView_programs);
    Dialog_doc_types::renew_doc_types(db, ui->tableView_doc_types);
    Dialog_good_types::renew_good_types(db, ui->tableView_good_types);
//    renew_cards(db, ui->tableView_cards);
//    renew_action_on_program_comboBox(db, ui->action_on_program);
//    renew_contr_on_card_comboBox(db, ui->contr_for_card);
//    renew_program_on_card_comboBox(db, ui->program_on_card);
//    renew_action_on_card_comboBox(db, ui->single_action_on_card);
}

Sale_department::~Sale_department()
{
    delete ui;
}

/* START ACTIONS TAB SLOTS BLOCK */

void Sale_department::on_add_action_button_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "add", ui->tableView_actions, old_action_data);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_tableView_actions_pressed(const QModelIndex &index)
{
    ui->update_action->setEnabled(true);
    ui->delete_action->setEnabled(true);
    ui->clear_action_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    QDate start = index.sibling(row, 2).data().toDate();
    QString str_start = start.toString("yyyy-MM-dd");
    QDate stop = index.sibling(row, 3).data().toDate();
    QString str_stop = stop.toString("yyyy-MM-dd");
    int percent = index.sibling(row, 1).data().toInt();
    QString str_percent = QString::number(percent);
    old_action_data[0] = str_start;
    old_action_data[1] = str_stop;
    qDebug() << old_action_data[0] << endl;
    old_action_data[2] = str_percent;
    old_action_data[3] = name;
    ui->action_buffer->setText(name);
}

void Sale_department::on_clear_action_buffer_clicked()
{
    ui->update_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
    ui->clear_action_buffer->setEnabled(false);
    ui->action_buffer->clear();
}

void Sale_department::on_update_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "update", ui->tableView_actions, old_action_data);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_delete_action_clicked()
{

    QString name = old_action_data[3];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити акцію '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".actions where action_name = '" + name +"';",
                "operator",
                this,
                3
        );
        Dialog_actions::renew_actions(db, ui->tableView_actions);
    };
}
/* END ACTIONS TAB SLOTS BLOCK */

/* START CONTRACTORS TAB SLOTS BLOCK */

void Sale_department::on_add_contractor_button_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "add",
                                                                    ui->tableView_contractors,
                                                                    old_contr_data);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
}

void Sale_department::on_tableView_contractors_pressed(const QModelIndex &index)
{
    ui->update_contractor->setEnabled(true);
    ui->delete_contr->setEnabled(true);
    ui->clear_contractor_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    QString phone = index.sibling(row, 1).data().toString();
    QString adress = index.sibling(row, 2).data().toString();
    QDate birth = index.sibling(row, 3).data().toDate();
    QString str_birth = birth.toString("yyyy-MM-dd");
    QString numb = index.sibling(row, 4).data().toString();
    if (str_birth != "") {
        ui->card_info->setEnabled(true);
    } else if (numb != "") {
        ui->card_info->setEnabled(false);
    }
    old_contr_data[0] = name;
    old_contr_data[1] = str_birth;
    old_contr_data[2] = numb;
    old_contr_data[3] = phone;
    old_contr_data[4] = adress;
    ui->contractor_buffer->setText(name);
}

void Sale_department::on_clear_contractor_buffer_clicked()
{
    ui->update_contractor->setEnabled(false);
    ui->delete_contr->setEnabled(false);
    ui->clear_contractor_buffer->setEnabled(false);
    ui->card_info->setEnabled(false);
    ui->contractor_buffer->clear();
}

void Sale_department::on_update_contractor_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "update",
                                                                    ui->tableView_contractors,
                                                                    old_contr_data);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
}

void Sale_department::on_card_info_clicked()
{
    Dialog_card_info * card_info = new Dialog_card_info(db,
                                                        ui->tableView_contractors,
                                                        ui->tableView_programs,
                                                        ui->tableView_actions,
                                                        old_contr_data
                                                      );
    card_info->setModal(true);
    card_info->show();
}


void Sale_department::on_delete_contr_clicked()
{
    QString name = old_contr_data[0];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити контрагента '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".contractors where contr_name = '" + name +"';",
                "operator",
                this,
                3
        );
        Dialog_contractors::renew_contractors(db, ui->tableView_contractors);
    };
}

/* END CONTRACTORS TAB SLOTS BLOCK */

/* START PROGRAMS TAB SLOTS BLOCK */

void Sale_department::on_add_program_button_clicked()
{
    Dialog_programs* dialog_actions = new Dialog_programs(db, "add", ui->tableView_programs, old_program_data);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_tableView_programs_pressed(const QModelIndex &index)
{
    ui->update_program_button->setEnabled(true);
    ui->delete_program_button->setEnabled(true);
    ui->action_on_program_info->setEnabled(true);
    ui->clear_program_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    QDate start = index.sibling(row, 1).data().toDate();
    QString str_start = start.toString("yyyy-MM-dd");
    QDate stop = index.sibling(row, 2).data().toDate();
    QString str_stop = stop.toString("yyyy-MM-dd");
    old_program_data[0] = str_start;
    old_program_data[1] = str_stop;
    old_program_data[2] = name;
    ui->program_buffer->setText(name);
}


void Sale_department::on_clear_program_buffer_clicked()
{
    ui->update_program_button->setEnabled(false);
    ui->delete_program_button->setEnabled(false);
    ui->clear_program_buffer->setEnabled(false);
    ui->action_on_program_info->setEnabled(false);
    ui->program_buffer->clear();
}

void Sale_department::on_update_program_button_clicked()
{
    Dialog_programs* dialog_programs = new Dialog_programs(db, "update", ui->tableView_programs, old_program_data);
    dialog_programs->setModal(true);
    dialog_programs->show();

}

void Sale_department::on_delete_program_button_clicked()
{
    QString name = old_program_data[2];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити програму '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".programs where program_name = '" + name + "';",
                "operator",
                this,
                3
        );
        Dialog_programs::renew_programs(db, ui->tableView_programs);
    };
}

void Sale_department::on_action_on_program_info_clicked()
{
    Dialog_program_info* program_info = new Dialog_program_info(db,
                                                                ui->tableView_programs,
                                                                ui->tableView_actions,
                                                                old_program_data);
    program_info->setModal(true);
    program_info->show();
}

/* END PROGRAMS TAB SLOTS BLOCK */


/* START DOCUMENT TYPES TAB SLOTS BLOCK */
void Sale_department::on_add_new_doc_type_clicked()
{
    Dialog_doc_types* dialog_doc_type = new Dialog_doc_types(db, "add", ui->tableView_doc_types, old_doc_type_data);
    dialog_doc_type->setModal(true);
    dialog_doc_type->show();
}

void Sale_department::on_tableView_doc_types_pressed(const QModelIndex &index)
{
    ui->update_doc_type->setEnabled(true);
    ui->delete_doc_type->setEnabled(true);
    ui->clear_doc_type_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    old_doc_type_data = name;
    ui->doc_type_buffer->setText(name);
}

void Sale_department::on_clear_doc_type_buffer_clicked()
{
    ui->update_doc_type->setEnabled(false);
    ui->delete_doc_type->setEnabled(false);
    ui->clear_doc_type_buffer->setEnabled(false);
    ui->doc_type_buffer->clear();
}

void Sale_department::on_update_doc_type_clicked()
{
    Dialog_doc_types* dialog_doc_type = new Dialog_doc_types(db, "update", ui->tableView_doc_types, old_doc_type_data);
    dialog_doc_type->setModal(true);
    dialog_doc_type->show();
}

void Sale_department::on_delete_doc_type_clicked()
{
    QString name = old_doc_type_data;
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити тип документа '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".doc_types where doc_type_name = '" + name +"';",
                "operator",
                this,
                3
        );
        Dialog_doc_types::renew_doc_types(db, ui->tableView_doc_types);
    };
}

/* END DOCUMENT TYPES SLOTS BLOCK */

/* START GOOD TYPES SLOTS BLOCK */

void Sale_department::on_add_new_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "add", ui->tableView_good_types, old_good_data);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
}

void Sale_department::on_tableView_good_types_pressed(const QModelIndex &index)
{
    ui->update_good_type->setEnabled(true);
    ui->delete_good_type->setEnabled(true);
    ui->clear_good_type_buffer->setEnabled(true);
    int row = index.row();
    old_good_data[0] = index.sibling(row, 0).data().toString(); // name
    old_good_data[3] = index.sibling(row, 1).data().toString(); // price
    old_good_data[1] = index.sibling(row, 2).data().toString(); // term
    old_good_data[2] = index.sibling(row, 3).data().toString(); // item
    ui->good_type_buffer->setText(old_good_data[0]);
}

void Sale_department::on_update_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "update", ui->tableView_good_types, old_good_data);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
}

void Sale_department::on_clear_good_type_buffer_clicked()
{
    ui->update_good_type->setEnabled(false);
    ui->delete_good_type->setEnabled(false);
    ui->clear_good_type_buffer->setEnabled(false);
    ui->good_type_buffer->clear();
}

void Sale_department::on_delete_good_type_clicked()
{
    QString name = old_good_data[0];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити вид товару '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".goods where good_name = '" + name + "';",
                "operator",
                this,
                3
        );
        Dialog_good_types::renew_good_types(db, ui->tableView_good_types);
    };
}
