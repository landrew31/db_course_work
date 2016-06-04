#include "dialog_firestaff.h"
#include "ui_dialog_firestaff.h"

Dialog_fireStaff::Dialog_fireStaff(DB_setup* db, int selectedStaffId, int selectedPersId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fireStaff)
{
    ui->setupUi(this);
    this->db = db;
    staffId = selectedStaffId;
    persId = selectedPersId;

    showInpValues();
    ui->fireDate->setDate(QDate::currentDate());
}

Dialog_fireStaff::~Dialog_fireStaff()
{
    delete ui;
}

void Dialog_fireStaff::showInpValues()
{
    QString queryText;
    QModelIndex index;

    queryText = QString(
            "select per_name, per_surname, posit_name "
                "from \"Myronenko_O\".show_staff "
                "where \"Id_person\" = %1;").arg(persId);
    QSqlQueryModel *modelStaff = db->getQueryModel(queryText);

    index = modelStaff->index(0, 0);
    QString name = index.data(Qt::DisplayRole).toString();

    index = modelStaff->index(0, 1);
    QString surname = index.data(Qt::DisplayRole).toString();
    ui->staffNameSurname->setText(name + " " + surname);

    index = modelStaff->index(0, 2);
    QString position = index.data(Qt::DisplayRole).toString();
    ui->positioin->setText(position);
}

void Dialog_fireStaff::accept()
{
    ui->buttonBox->setDisabled(true);

    QString fireDate = ui->fireDate->date().toString("yyyy-MM-dd");
    if (DEBUGMODE) qDebug() << "fire" << staffId << "staff from position on" << fireDate << "date" << endl;
    QString queryText = QString("select \"Myronenko_O\".fire_staff(%1, '%2');").arg(staffId).arg(fireDate);
    db->executeQuery(queryText, "admin", this, 2);

    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
