#include "dialog_programs.h"
#include "ui_dialog_programs.h"

Dialog_programs::Dialog_programs(DB_setup *db,
                                 QString mode,
                                 QTableView* table,
                                 QString *old_data,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_programs)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;

    QString action = "";
    if (mode == "add") {
        action = "Додати";
        this->setWindowTitle("Додавання програми");
    } else if (mode == "update") {
        action = "Редагувати";
        this->setWindowTitle("Редагування програми '" + old_data[2] + "'");
        QDate start=QDate::fromString(old_data[0],"yyyy-MM-dd");
        QDate stop=QDate::fromString(old_data[1],"yyyy-MM-dd");
        ui->start_program_date->setDate(start);
        ui->stop_program_date->setDate(stop);
        ui->program_name_field->setText(old_data[2]);
    };
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_programs::~Dialog_programs()
{
    delete ui;
}

void Dialog_programs::renew_programs(DB_setup* db, QTableView* table)
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_programs;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва програми"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Початок програми"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Кінець програми"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
    table->resizeColumnToContents(2);

    DB_setup::table_column_entire_width(table);
}

void Dialog_programs::on_clear_program_form_clicked()
{
    ui->program_name_field->clear();
    ui->start_program_date->date();
    ui->stop_program_date->date();
}

void Dialog_programs::on_buttonBox_accepted()
{
    QString start = ui->start_program_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_program_date->date().toString("yyyy-MM-dd");
    QString name = ui->program_name_field->text();
    QString query = "";
    if (mode == "add") {
        query = "insert into \"Lupa_A\".programs (day_start, day_stop, program_name) values('"+ start + "','" + stop + "','" + name + "');";
        db->executeQuery(query, "operator", this, 1);
    } else if (mode == "update") {
        query = "select update_program('" + old_data[2] + "','" + name + "','" + start + "','" + stop + "');";
        db->executeQuery(query, "operator", this, 0);
    };

    renew_programs(db, table);
}
