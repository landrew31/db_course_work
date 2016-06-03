#include "dialog_actions.h"
#include "ui_dialog_actions.h"

Dialog_actions::Dialog_actions(DB_setup *db,
                               QString mode,
                               QTableView* table,
                               QString *old_data,
                               QDateEdit *date_edit,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_actions)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;
    this->date_edit = date_edit;


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
        ui->start_action_date->setEnabled(false);
        ui->stop_action_date->setEnabled(false);
        ui->action_percent_field->setEnabled(false);
        ui->clear_action_form->setEnabled(false);
    };
    ui->start_action_date->setDate(QDate::currentDate());
    ui->stop_action_date->setDate(QDate::currentDate());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_actions::~Dialog_actions()
{
    delete ui;
}

QSortFilterProxyModel* Dialog_actions::renew_actions(DB_setup* db, QTableView* table, QDateEdit *date_field )
{
    QString date = date_field->date().toString("yyyy-MM-dd");
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_actions where day_stop >= '" + date + "' and day_start <= '" + date + "';");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва акції"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Відсоток по акції"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Початок акції"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Кінець акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(0);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);

    DB_setup::table_column_entire_width(table);
    return proxyModel;
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
        db->executeQuery(query, db->getUser(), this, 1);
    } else if (mode == "update") {
        query = "select update_action('" + old_data[3] + "','" + name + "','" + QString::number(percent) + "','" + start + "','" + stop + "');";
        db->executeQuery(query, db->getUser(), this, 0);
    };
    emit actionsChanged();
    QSortFilterProxyModel *proxy = renew_actions(db, table, date_edit);
}
