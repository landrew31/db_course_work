#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogentry.h"
#include <QDebug>

MainWindow::MainWindow(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;
    renew_actions();
    renew_contractors();
    renew_programs();
    renew_cards();
    renew_action_on_program_comboBox();
    renew_contr_on_card_comboBox();
    renew_program_on_card_comboBox();
    renew_action_on_card_comboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* RENEW COMBOBOXES BLOCK */
void MainWindow::renew_action_on_program_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions ORDER BY action_name;");
    ui->action_on_program->setModel(model);
    ui->action_on_program->setCurrentIndex(-1);
}

void MainWindow::renew_contr_on_card_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT contr_name FROM \"Lupa_A\".contractors ORDER BY contr_name;");
    ui->contr_for_card->setModel(model);
    ui->contr_for_card->setCurrentIndex(-1);
}

void MainWindow::renew_program_on_card_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT program_name FROM \"Lupa_A\".action_programs ORDER BY program_name;");
    ui->program_on_card->setModel(model);
    ui->program_on_card->setCurrentIndex(-1);
}

void MainWindow::renew_action_on_card_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions ORDER BY action_name;");
    ui->single_action_on_card->setModel(model);
    ui->single_action_on_card->setCurrentIndex(-1);
}
/* END RENEW COMBOBOXES BLOCK */

/* RENEW VIEWS BLOCK */
void MainWindow::renew_actions()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_actions;");

    model->setHeaderData(0, Qt::Horizontal, tr("Назва акції"));
    model->setHeaderData(1, Qt::Horizontal, tr("Відсоток по акції"));
    model->setHeaderData(2, Qt::Horizontal, tr("Початок акції"));
    model->setHeaderData(3, Qt::Horizontal, tr("Кінець акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView_actions->setModel(proxyModel);
    ui->tableView_actions->setSortingEnabled(true);
    ui->tableView_actions->resizeColumnToContents(0);
    ui->tableView_actions->resizeColumnToContents(1);
    ui->tableView_actions->resizeColumnToContents(2);
    ui->tableView_actions->resizeColumnToContents(3);
}

void MainWindow::renew_contractors()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_contractors;");

    model->setHeaderData(0, Qt::Horizontal, tr("Ім'я контрагента"));
    model->setHeaderData(1, Qt::Horizontal, tr("Телефон"));
    model->setHeaderData(2, Qt::Horizontal, tr("Адреса"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата народження (фіз.особа)"));
    model->setHeaderData(4, Qt::Horizontal, tr("Номер в реєстрі (юр.особа)"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView_contractors->setModel(proxyModel);
    ui->tableView_contractors->setSortingEnabled(true);
    ui->tableView_contractors->resizeColumnToContents(0);
    ui->tableView_contractors->resizeColumnToContents(1);
    ui->tableView_contractors->resizeColumnToContents(2);
    ui->tableView_contractors->resizeColumnToContents(3);
    ui->tableView_contractors->resizeColumnToContents(4);
}

void MainWindow::renew_programs()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_not_finished_actions_on_programs;");

    model->setHeaderData(0, Qt::Horizontal, tr("Назва програми"));
    model->setHeaderData(1, Qt::Horizontal, tr("Доступні зараз акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView_programs->setModel(proxyModel);
    ui->tableView_programs->setSortingEnabled(true);
    ui->tableView_programs->resizeColumnToContents(0);
    ui->tableView_programs->resizeColumnToContents(1);
    ui->action_on_program->setCurrentIndex(-1);
}

void MainWindow::renew_cards()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_cards;");

    model->setHeaderData(0, Qt::Horizontal, tr("Контрагент"));
    model->setHeaderData(1, Qt::Horizontal, tr("Доступні зараз програми"));
    model->setHeaderData(2, Qt::Horizontal, tr("Доступні зараз акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView_cards->setModel(proxyModel);
    ui->tableView_cards->setSortingEnabled(true);
    ui->tableView_cards->resizeColumnToContents(0);
    ui->tableView_cards->resizeColumnToContents(1);
    ui->tableView_cards->resizeColumnToContents(2);
    ui->contr_for_card->setCurrentIndex(-1);
    ui->program_on_card->setCurrentIndex(-1);
    ui->single_action_on_card->setCurrentIndex(-1);
}

/* END RENEW VIEWS BLOCK */

/* START ACTIONS TAB SLOTS BLOCK */

void MainWindow::on_add_action_button_clicked()
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
    renew_actions();

}

void MainWindow::on_tableView_actions_pressed(const QModelIndex &index)
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

void MainWindow::on_update_action_clicked()
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
    renew_actions();
}

void MainWindow::on_clear_action_form_clicked()
{
    ui->action_name_field->clear();
    ui->action_percent_field->clear();
    ui->start_action_date->date();
    ui->stop_action_date->date();
    ui->add_action_button->setEnabled(true);
    ui->update_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
}

void MainWindow::on_delete_action_clicked()
{
    QString name = ui->action_name_field->text();
    db->executeQuery(
                "delete from \"Lupa_A\".actions where action_name = '" + name +"';",
                "operator",
                this
    );
    renew_actions();
}

/* END ACTIONS TAB SLOTS BLOCK */

/* START CONTRACTORS TAB SLOTS BLOCK */

void MainWindow::on_is_individual_clicked(bool checked)
{
    ui->birthday_field->setEnabled(checked);
}

void MainWindow::on_is_entity_clicked(bool checked)
{
    ui->state_number_field->setEnabled(checked);
}

void MainWindow::on_add_contractor_button_clicked()
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
    renew_contractors();
    renew_contr_on_card_comboBox();
}

void MainWindow::on_tableView_contractors_pressed(const QModelIndex &index)
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

void MainWindow::on_update_contractor_clicked()
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
    renew_contractors();
}

void MainWindow::on_clear_contr_form_clicked()
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

void MainWindow::on_delete_contr_clicked()
{
    QString name = ui->contractor_name_field->text();
    db->executeQuery(
                "delete from \"Lupa_A\".contractors where contr_name = '" + name +"';",
                "operator",
                this
    );
    renew_contractors();
}

/* END CONTRACTORS TAB SLOTS BLOCK */

/* START PROGRAMS TAB SLOTS BLOCK */

void MainWindow::on_add_program_button_clicked()
{
    QString name = ui->program_name_field->text();
    QString action_in_program = ui->action_on_program->currentText();
    db->executeQuery(
                "select insert_new_program('"+ name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs();
}

void MainWindow::on_clear_program_form_clicked()
{
    ui->program_name_field->clear();
    ui->action_on_program->setCurrentIndex(-1);
    ui->add_program_button->setEnabled(true);
    ui->update_program_button->setEnabled(false);
    ui->add_new_action_to_program_button->setEnabled(false);
    ui->delete_action_from_program_button->setEnabled(false);
    ui->delete_program_button->setEnabled(false);
}

void MainWindow::on_tableView_programs_pressed(const QModelIndex &index)
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

void MainWindow::on_update_program_button_clicked()
{
    QString name = ui->program_name_field->text();

    db->executeQuery(
                "select update_program_name('"+ old_program_name + "','" + name + "');",
                "operator",
                this
    );
    renew_programs();
}

void MainWindow::on_delete_program_button_clicked()
{
    QString name = ui->program_name_field->text();

    db->executeQuery(
                "delete from \"Lupa_A\".action_programs where program_name = '" + name + "';",
                "operator",
                this
    );
    renew_programs();
}

void MainWindow::on_add_new_action_to_program_button_clicked()
{
    QString action_in_program = ui->action_on_program->currentText();

    db->executeQuery(
                "select insert_new_action_in_program('"+ old_program_name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs();
}

void MainWindow::on_delete_action_from_program_button_clicked()
{
    QString action_in_program = ui->action_on_program->currentText();
    db->executeQuery(
                "select delete_action_from_program('"+ old_program_name + "','" + action_in_program + "');",
                "operator",
                this
    );
    renew_programs();
}

/* END PROGRAMS TAB SLOTS BLOCK */

/* START CARDS TAB SLOTS BLOCK */

void MainWindow::on_add_card_clicked()
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
    renew_cards();
}

void MainWindow::on_clear_card_form_clicked()
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

void MainWindow::on_tableView_cards_pressed(const QModelIndex &index)
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

void MainWindow::on_add_program_on_card_clicked()
{
    QString program_on_card = ui->program_on_card->currentText();

    db->executeQuery(
                "select insert_new_program_on_card('"+ old_card_name + "','" + program_on_card + "');",
                "operator",
                this
    );
    renew_cards();
}

void MainWindow::on_add_single_action_on_card_clicked()
{
    QString action_on_card = ui->single_action_on_card->currentText();

    db->executeQuery(
                "select insert_new_action_on_card('"+ old_card_name + "','" + action_on_card + "');",
                "operator",
                this
    );
    renew_cards();
}

void MainWindow::on_delete_program_from_card_clicked()
{
    QString program_on_card = ui->program_on_card->currentText();

    db->executeQuery(
                "select delete_program_from_card('"+ old_card_name + "','" + program_on_card + "');",
                "operator",
                this
    );
    qDebug() << "select delete_program_from_card('"+ old_card_name + "','" + program_on_card + "');" << endl;
    renew_cards();
}

void MainWindow::on_delete_single_action_from_card_clicked()
{
    QString action_on_card = ui->single_action_on_card->currentText();

    db->executeQuery(
                "select delete_action_from_card('"+ old_card_name + "','" + action_on_card + "');",
                "operator",
                this
    );
    renew_cards();
}
