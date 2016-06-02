#include "dialog_addstaff.h"
#include "ui_dialog_addstaff.h"

Dialog_addStaff::Dialog_addStaff(DB_setup* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addStaff)
{
    ui->setupUi(this);
    this->db = db;
    showInpValues();
}

Dialog_addStaff::~Dialog_addStaff()
{
    delete ui;
}

void Dialog_addStaff::showInpValues()
{
    updatePersSelect();
    updateOpenedVacancies();
    ui->startDate->setDate(QDate::currentDate());
}

void Dialog_addStaff::updatePersSelect()
{
    QString queryText;
    QModelIndex index;

    queryText = "select per_name, per_surname, \"Id_person\" "
            "from \"Myronenko_O\".show_free_persons;";
    modelAllPersons = db->getQueryModel(queryText);
    int modelRowsCount = modelAllPersons->rowCount();
    ui->selectPerson->clear();
    for (int i=0; i < modelRowsCount; i++)
    {
        index = modelAllPersons->index(i, 0);
        QString personName = index.data(Qt::DisplayRole).toString();
        index = modelAllPersons->index(i, 1);
        QString personSurname = index.data(Qt::DisplayRole).toString();
        ui->selectPerson->addItem(personName + " " + personSurname);
    }
}

void Dialog_addStaff::updateOpenedVacancies()
{
    QString queryText;
    QModelIndex index;

    queryText = "select * from \"Myronenko_O\".show_vacancies;";
    modelAllOpenedVacs = db->getQueryModel(queryText);
    int modelRowsCount = modelAllOpenedVacs->rowCount();
    ui->selectVacancy->clear();
    for (int i=0; i < modelRowsCount; i++)
    {
        index = modelAllOpenedVacs->index(i, 0);
        QString positName = index.data(Qt::DisplayRole).toString();
        index = modelAllOpenedVacs->index(i, 1);
        int vacCount = index.data(Qt::DisplayRole).toInt();
        if (vacCount > 0) {
            ui->selectVacancy->addItem(positName);
        }
    }
}

void Dialog_addStaff::on_createPerson_clicked()
{
    Dialog_editPersInfo* dialog_editPersInfo = new Dialog_editPersInfo(db, -1, this);
    dialog_editPersInfo->show();
    connect(dialog_editPersInfo, SIGNAL(accepted()), this, SLOT(updatePersSelect()));
}

void Dialog_addStaff::on_openVacancy_clicked()
{
    Dialog_openVacancy* dialog_openVacancy = new Dialog_openVacancy(db, this);
    dialog_openVacancy->show();
    connect(dialog_openVacancy, SIGNAL(accepted()), this, SLOT(updateOpenedVacancies()));
}

int Dialog_addStaff::searchIdBynameSurnameInModel(QString key, QSqlQueryModel* model, int idPosit, int keyPosit1, int keyPosit2)
{
    int id = -1;
    QModelIndex index;
    int rowCount = model->rowCount();
    for (int i=0; i < rowCount; i++)
    {
        index = model->index(i, keyPosit1);
        QString name = index.data(Qt::DisplayRole).toString();
        index = model->index(i, keyPosit2);
        QString surname = index.data(Qt::DisplayRole).toString();
        if ( key.compare(name + " " + surname) == 0 )
        {
            index = model->index(i, idPosit);
            id = index.data(Qt::DisplayRole).toInt();
            break;
        }
    }
    return id;
}

void Dialog_addStaff::accept()
{
    ui->buttonBox->setDisabled(true);

    QString selectedPerson = ui->selectPerson->currentText();
    QString selectedVacancy = ui->selectVacancy->currentText();

    int id_person = searchIdBynameSurnameInModel(selectedPerson, modelAllPersons, 2, 0, 1);
    int id_position = searchIdByNameInModel(selectedVacancy, modelAllOpenedVacs, 2, 0);
    QString date = ui->startDate->date().toString("yyyy-MM-dd");

    if (DEBUGMODE) qDebug() << "new staff: personId" << id_person << ", positId" << id_position << ", date" << date;
    QString queryText = QString(
        "select \"Myronenko_O\".add_person_on_position(%1, %2, '%3');"
    ).arg(id_person).arg(id_position).arg(date);
    db->executeQuery(queryText, "admin", this, 1);

    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
