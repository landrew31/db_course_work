#include "dialog_contractors.h"
#include "ui_dialog_contractors.h"

Dialog_contractors::Dialog_contractors(DB_setup *db,
                                       QString mode,
                                       QTableView* table,
                                       QString *old_data,
                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_contractors)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_data = old_data;


    QString action = "";
    if (mode == "add") {
        action = "Додати";
        this->setWindowTitle("Додавання контрагента");
    } else if (mode == "update") {
        action = "Редагувати";
        this->setWindowTitle("Редагування контраента '" + old_data[3] + "'");
        ui->phone_field->setText(old_data[3]);
        ui->adress_field->setText(old_data[4]);
        ui->phone_field->setEnabled(true);
        ui->adress_field->setEnabled(true);
        if (old_data[1] != "") {
            ui->is_individual->setChecked(true);
            ui->contractor_name_field->setText(old_data[0]);
            QDate birth = QDate::fromString(old_data[1], "yyyy-MM-dd");
            ui->birthday_field->setDate(birth);
            ui->contractor_name_field->setEnabled(true);
            ui->birthday_field->setEnabled(true);
            ui->is_entity->setEnabled(false);
        } else if (old_data[2] != "") {
            ui->is_entity->setChecked(true);
            ui->company_name_field->setText(old_data[0]);
            ui->state_number_field->setText(old_data[2]);
            ui->company_name_field->setEnabled(true);
            ui->state_number_field->setEnabled(true);
            ui->is_entity->setEnabled(false);
        };
    };
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_contractors::~Dialog_contractors()
{
    delete ui;
}

void Dialog_contractors::renew_contractors(DB_setup* db, QTableView* table)
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_contractors;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ім'я контрагента"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Телефон"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Адреса"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Дата народження (фіз.особа)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Номер в реєстрі (юр.особа)"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
    table->resizeColumnToContents(2);
    table->resizeColumnToContents(3);
    table->resizeColumnToContents(4);
}

void Dialog_contractors::on_is_individual_clicked(bool checked)
{
    ui->contractor_name_field->setEnabled(checked);
    ui->birthday_field->setEnabled(checked);
    ui->company_name_field->setEnabled(!checked);
    ui->state_number_field->setEnabled(!checked);
    if (!ui->phone_field->isEnabled()) {
        ui->phone_field->setEnabled(checked);
        ui->adress_field->setEnabled(checked);
    };
    ui->is_entity->setChecked(!checked);
}

void Dialog_contractors::on_is_entity_clicked(bool checked)
{
    ui->contractor_name_field->setEnabled(!checked);
    ui->birthday_field->setEnabled(!checked);
    ui->company_name_field->setEnabled(checked);
    ui->state_number_field->setEnabled(checked);
    if (!ui->phone_field->isEnabled()) {
        ui->phone_field->setEnabled(checked);
        ui->adress_field->setEnabled(checked);
    };
    ui->is_individual->setChecked(!checked);
}

void Dialog_contractors::on_clear_contr_form_clicked()
{
    ui->is_individual->setChecked(false);
    ui->is_entity->setChecked(false);

    ui->contractor_name_field->clear();
    ui->company_name_field->clear();
    ui->phone_field->clear();
    ui->adress_field->clear();
    ui->state_number_field->clear();
    ui->birthday_field->date();

    ui->contractor_name_field->setEnabled(false);
    ui->company_name_field->setEnabled(false);
    ui->phone_field->setEnabled(false);
    ui->adress_field->setEnabled(false);
    ui->birthday_field->setEnabled(false);
    ui->state_number_field->setEnabled(false);
}



void Dialog_contractors::on_buttonBox_accepted()
{
    QString phone = ui->phone_field->text();
    QString adress = ui->adress_field->text();
    QString birth = "";
    QString number = "";
    QString name = "";

    if (ui->is_individual->isChecked()) {
        birth = ui->birthday_field->date().toString("yyyy.MM.dd");
        name = ui->contractor_name_field->text();
    }
    if (ui->is_entity->isChecked()) {
        number = ui->state_number_field->text();
        name = ui->company_name_field->text();
    };
    QString query = "";
    if (mode == "add") {
        query = "select insert_new_contractor('"+ name + "','" + phone + "','" + adress + "','" + birth + "','" + number + "');";
    } else if (mode == "update") {
        query = "select update_contractor('" + old_data[0] + "','" + name + "','" + phone + "','" + adress + "','" + birth + "','" + number + "');";
    };
    db->executeQuery(query, "operator", this);
    renew_contractors(db, table);
}
