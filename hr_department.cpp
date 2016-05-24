#include "hr_department.h"
#include "dialogentry.h"


HR_department::HR_department(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HR_department)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;

    showStaffTable();
}

HR_department::~HR_department()
{
    delete ui;
}

void HR_department::showStaffTable()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Myronenko_O\".show_persons;");

    model->setHeaderData(0, Qt::Horizontal, tr("Ім'я"));
    model->setHeaderData(1, Qt::Horizontal, tr("Прізвище"));
    model->setHeaderData(2, Qt::Horizontal, tr("Освіта"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_staff->setModel(proxyModel);
    ui->table_staff->setSortingEnabled(true);
    ui->table_staff->resizeColumnToContents(0);
    ui->table_staff->resizeColumnToContents(1);
    ui->table_staff->resizeColumnToContents(2);
}

//void HR_department::on_button_addStuff_clicked()
//{

//    QString name = ui->line_pername->text();
//    QString surname = ui->line_persurname->text();
//    QString birthday = ui->date_perbirth->date().toString("yyyy-MM-dd");
//    QString education = ui->line_peredu->text();

//    qDebug() << name << surname << birthday << education;

//    db->executeQuery(
//                "insert into \"Myronenko_O\".person (per_name, per_surname, birthday, education) values('"
//                    + name + "','"
//                    + surname + "','"
//                    + birthday + "','"
//                    + education + "');",
//                "operator",
//                this
//    );
//    showStaffTable();
//}
void HR_department::on_button_closeWindow_clicked()
{
    this->close();
}

void HR_department::on_button_editPersInfo_clicked()
{
    Dialog_editPersInfo* dialog_editPersInfo = new Dialog_editPersInfo(db);
    dialog_editPersInfo->setModal(true);
    dialog_editPersInfo->show();
}
