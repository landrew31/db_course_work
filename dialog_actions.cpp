#include "dialog_actions.h"
#include "ui_dialog_actions.h"

Dialog_actions::Dialog_actions(DB_setup *db, QString mode, QTableView* table, QString *old_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_actions)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;


    QString action = "";
    if (mode == "add") {
        action = "Додати";
        this->setWindowTitle("Додавання акції");
    } else if (mode == "update") {
        action = "Редагувати";
        this->setWindowTitle("Редагування акції '" + old_data[3] + "'");
        QDate start=QDate::fromString(old_data[0],"yyyy-MM-dd");
        QDate stop=QDate::fromString(old_data[1],"yyyy-MM-dd");
        ui->start_action_date->setDate(start);
        ui->stop_action_date->setDate(stop);
        ui->action_percent_field->setText(old_data[2]);
        ui->action_name_field->setText(old_data[3]);
    };
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

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

void Dialog_actions::on_clear_action_form_clicked()
{
    ui->action_name_field->clear();
    ui->action_percent_field->clear();
    ui->start_action_date->date();
    ui->stop_action_date->date();
}

void Dialog_actions::on_buttonBox_accepted()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    QString name = ui->action_name_field->text();
    int percent = ui->action_percent_field->text().toInt();
    QString query = "";
    if (mode == "add") {
        query = "insert into \"Lupa_A\".actions (day_start, day_stop, action_name, percent) values('"+ start + "','" + stop + "','" + name + "','" + QString::number(percent) + "');";
    } else if (mode == "update") {
        query = "select update_action('" + old_data[3] + "','" + name + "','" + QString::number(percent) + "','" + start + "','" + stop + "');";
    };
    db->executeQuery(query, "operator", this);
    renew_actions(db, table);
}
