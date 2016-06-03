#include "dialog_good_types.h"
#include "ui_dialog_good_types.h"

Dialog_good_types::Dialog_good_types(DB_setup *db,
                                     QString mode,
                                     QTableView *table,
                                     QString *old_data,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_good_types)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;

    QString action = "";
    if (mode == "add") {
        action = "Додати";
    } else if (mode == "update") {
        action = "Редагувати";
        this->setWindowTitle("Редагування типу товару '" + old_data[0] + "'");
        ui->good_type_name->setText(old_data[0]);
        ui->expiration_date->setText(old_data[1]);
        if (old_data[2] == "Поштучний") {
            ui->is_item->setChecked(true);
            ui->is_loose->setEnabled(false);
        } else if (old_data[2] == "Розсипний") {
            ui->is_loose->setChecked(true);
            ui->is_item->setEnabled(false);
        };
        ui->price_for_one->setText(old_data[3]);
    };
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_good_types::~Dialog_good_types()
{
    delete ui;
}


QSortFilterProxyModel* Dialog_good_types::renew_good_types(DB_setup* db, QTableView* table )
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_good_types;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва товару"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ціна одиниці"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Термін придатності"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Агрегатний стан"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);

    DB_setup::table_column_entire_width(table);
    return proxyModel;
}
void Dialog_good_types::on_clear_good_type_form_clicked()
{
    ui->good_type_name->clear();
    ui->expiration_date->clear();
    ui->is_item->setChecked(false);
    ui->is_loose->setChecked(false);
    ui->price_for_one->clear();
}

void Dialog_good_types::on_buttonBox_accepted()
{
    QString name = ui->good_type_name->text();
    QString term = ui->expiration_date->text();
    QString item = "";
    if (ui->is_item->isChecked()) {
        item = "Поштучний";
    } else if (ui->is_loose->isChecked()) {
        item = "Розсипний";
    };
    QString price = ui->price_for_one->text();
    QString query = "";
    if (mode == "add") {
        query = "insert into \"Lupa_A\".goods (good_name,term,item,price_per_one) values('"+ name + "','" + term + "','" + item + "','" + price + "');";
        db->executeQuery(query, "operator", this, 1);
    } else if (mode == "update") {
        query = "select update_good_type('"+ old_data[0] + "','" + name + "','" + term + "','" + item + "','" + price + "');";
        db->executeQuery(query, "operator", this, 0);
    };
    emit goodtypesChanged();
    QSortFilterProxyModel* proxy = renew_good_types(db, table);
}
