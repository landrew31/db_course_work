#include "dialog_programs.h"
#include "ui_dialog_programs.h"

Dialog_programs::Dialog_programs(DB_setup *db,
                                 QString mode,
                                 QTableView* table,
                                 QString *old_data,
                                 QDateEdit *date_field,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_programs)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;
    this->date_edit = date_field;

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
    ui->start_program_date->setDate(QDate::currentDate());
    ui->stop_program_date->setDate(QDate::currentDate());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_programs::~Dialog_programs()
{
    delete ui;
}

QSortFilterProxyModel* Dialog_programs::renew_programs(DB_setup* db, QTableView* table, QDateEdit* date_field)
{
    QString date = date_field->date().toString("yyyy-MM-dd");
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_programs where day_stop >= '" + date + "' and day_start <= '" + date + "';");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва програми"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Початок програми"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Кінець програми"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);

    DB_setup::table_column_entire_width(table);
    return proxyModel;
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
    qDebug() << "work" << endl;
    if (mode == "add") {
        query = "insert into \"Lupa_A\".programs (day_start, day_stop, program_name) values('"+ start + "','" + stop + "','" + name + "');";
        qDebug() << query << endl;
        db->executeQuery(query, db->getUser(), this, 1);
    } else if (mode == "update") {
        query = "select update_program('" + old_data[2] + "','" + name + "','" + start + "','" + stop + "');";
        db->executeQuery(query, db->getUser(), this, 2);
    };
    emit programsChanged();

    QSortFilterProxyModel *proxy = renew_programs(db, table, date_edit);
}
