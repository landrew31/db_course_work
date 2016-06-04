#include "dialog_changeposition.h"
#include "ui_dialog_changeposition.h"

Dialog_changePosition::Dialog_changePosition(DB_setup* db, int selectedStaffId, int selectedPersId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_changePosition)
{
    ui->setupUi(this);
    this->db = db;
    staffId = selectedStaffId;
    persId = selectedPersId;
    showInpValues();
    ui->changeDate->setDate(QDate::currentDate());
}

Dialog_changePosition::~Dialog_changePosition()
{
    delete ui;
}

void Dialog_changePosition::showInpValues()
{
    QString queryText;
    QModelIndex index;

    queryText = QString("select * from \"Myronenko_O\".show_shortStaffInfo where \"Id_staff\" = %1;").arg(staffId);
    QSqlQueryModel *model = db->getQueryModel(queryText);

    index = model->index(0, 1);
    QString name = index.data(Qt::DisplayRole).toString();
    index = model->index(0, 2);
    QString surname = index.data(Qt::DisplayRole).toString();
    index = model->index(0, 3);
    QString currPosition = index.data(Qt::DisplayRole).toString();
    ui->staffNameSurname->setText(name + " " + surname);
    ui->currentPosition->setText(currPosition);

    updatePositSelect();
}

void Dialog_changePosition::updatePositSelect()
{
    QString queryText;
    QModelIndex index;

    queryText = "select * from \"Myronenko_O\".show_vacancies;";
    modelAllOpenedVacs = db->getQueryModel(queryText);
    int modelRowsCount = modelAllOpenedVacs->rowCount();
    ui->selectNewPosition->clear();
    for (int i=0; i < modelRowsCount; i++)
    {
        index = modelAllOpenedVacs->index(i, 0);
        QString positName = index.data(Qt::DisplayRole).toString();
        index = modelAllOpenedVacs->index(i, 1);
        int vacCount = index.data(Qt::DisplayRole).toInt();
        if (vacCount > 0) {
            ui->selectNewPosition->addItem(positName);
        }
    }
}

void Dialog_changePosition::on_openNewVacancy_clicked()
{
    Dialog_openVacancy* dialog_openVacancy = new Dialog_openVacancy(db, this);
    dialog_openVacancy->show();
    connect(dialog_openVacancy, SIGNAL(accepted()), this, SLOT(updatePositSelect()));
}

void Dialog_changePosition::accept()
{
    ui->buttonBox->setDisabled(true);

    QString selectedVacancy = ui->selectNewPosition->currentText();
    int selectedPositId = searchIdByNameInModel(selectedVacancy, modelAllOpenedVacs, 2, 0);
    QString changeDate = ui->changeDate->date().toString("yyyy-MM-dd");

    if (DEBUGMODE) qDebug() << "change position of" << persId << "person to" << selectedPositId << "position";
    QString queryText = QString("select \"Myronenko_O\".change_staff_position(%1, %2, %3, '%4');").arg(persId).arg(staffId).arg(selectedPositId).arg(changeDate);
    db->executeQuery(queryText, "admin", this, 2);

    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
