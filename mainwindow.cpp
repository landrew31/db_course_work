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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_renew_actions_button_clicked()
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
    QString adress = ui->address_field->text();
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
}

void MainWindow::on_renew_contr_button_clicked()
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
