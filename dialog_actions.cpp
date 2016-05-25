#include "dialog_actions.h"
#include "ui_dialog_actions.h"

Dialog_actions::Dialog_actions(DB_setup *db, QString mode, QTableView* table, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_actions)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
}

Dialog_actions::~Dialog_actions()
{
    delete ui;
}

void Dialog_actions::renew_actions(DB_setup* db, QTableView* table )
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_actions;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва акції"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Відсоток по акції"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Початок акції"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Кінець акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
    table->resizeColumnToContents(2);
    table->resizeColumnToContents(3);
}

void Dialog_actions::on_buttonBox_accepted()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    QString name = ui->action_name_field->text();
    int percent = ui->action_percent_field->text().toInt();
    QString query = "insert into \"Lupa_A\".actions (day_start, day_stop, action_name, percent) values('"+ start + "','" + stop + "','" + name + "','" + QString::number(percent) + "');";
    db->executeQuery(query, "operator", this);
    renew_actions(db, table);
}
