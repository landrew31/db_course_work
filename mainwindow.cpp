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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renew_actions()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_actions;");

    model->setHeaderData(0, Qt::Horizontal, tr("Назва акції"));
    model->setHeaderData(1, Qt::Horizontal, tr("Початок акції"));
    model->setHeaderData(2, Qt::Horizontal, tr("Кінець акції"));
    model->setHeaderData(3, Qt::Horizontal, tr("Відсоток по акції"));
    ui->tableView_actions->setModel(model);
    ui->tableView_actions->resizeColumnToContents(0);
    ui->tableView_actions->resizeColumnToContents(1);
    ui->tableView_actions->resizeColumnToContents(2);
    ui->tableView_actions->resizeColumnToContents(3);

//    qDebug() << result;
}

void MainWindow::renew_contractors()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_contractors;");


    model->setHeaderData(0, Qt::Horizontal, tr("Ім'я контрагента"));
    model->setHeaderData(1, Qt::Horizontal, tr("Телефон"));
    model->setHeaderData(2, Qt::Horizontal, tr("Адреса"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата народження (фіз.особа)"));
    model->setHeaderData(4, Qt::Horizontal, tr("Номер в реєстрі (юр.особа)"));
    ui->tableView_contractors->setModel(model);
    ui->tableView_contractors->resizeColumnToContents(0);
    ui->tableView_contractors->resizeColumnToContents(1);
    ui->tableView_contractors->resizeColumnToContents(2);
    ui->tableView_contractors->resizeColumnToContents(3);
    ui->tableView_contractors->resizeColumnToContents(4);

//    qDebug() << result;
}

void MainWindow::on_add_action_button_clicked()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    QString name = ui->action_name_field->text();
    int percent = ui->action_percent_field->text().toInt();

    qDebug() << start << stop << percent;

    db->executeQuery(
                "insert into \"Lupa_A\".actions (day_start, day_stop, action_name, percent) values('"+ start + "','" + stop + "','" + name + "', :percent);",
                "operator",
                this
    );
    renew_actions();

}

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
}

void MainWindow::on_tableView_contractors_pressed(const QModelIndex &index)
{
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
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
