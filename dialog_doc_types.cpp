#include "dialog_doc_types.h"
#include "ui_dialog_doc_types.h"

Dialog_doc_types::Dialog_doc_types(DB_setup *db,
                                   QString mode,
                                   QTableView* table,
                                   QString old_type,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_doc_types)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table = table;
    this->old_type = old_type;

    QString action = "";
    if (mode == "add") {
        action = "Додати";
        this->setWindowTitle("Додавання типу документу");
    } else if (mode == "update") {
        action = "Редагувати";
        this->setWindowTitle("Редагування типу '"+ old_type +"'");
        ui->doc_type_name->setText(old_type);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(action);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");
}

Dialog_doc_types::~Dialog_doc_types()
{
    delete ui;
}

void Dialog_doc_types::renew_doc_types(DB_setup* db, QTableView* table )
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_doc_types;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва типу документу"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);

    DB_setup::table_column_entire_width(table);
}
void Dialog_doc_types::on_clear_doc_type_form_clicked()
{
    ui->doc_type_name->clear();
}

void Dialog_doc_types::on_buttonBox_accepted()
{

    QString name = ui->doc_type_name->text();

    QString query = "";
    if (mode == "add") {
        query = "insert into \"Lupa_A\".doc_types (doc_type_name) values('" + name + "');";
        db->executeQuery(query, "operator", this, 1);
    } else if (mode == "update") {
        query = "select update_doc_type('" + old_type + "','" + name + "');";
        db->executeQuery(query, "operator", this, 0);
    };
    emit doctypesChanged();
    renew_doc_types(db, table);
}
