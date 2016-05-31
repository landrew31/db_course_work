#include "dialog_removevacancy.h"
#include "ui_dialog_removevacancy.h"

Dialog_removeVacancy::Dialog_removeVacancy(DB_setup* db, int selectedPositId, QString positName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_removeVacancy)
{
    ui->setupUi(this);
    this->db = db;
    positId = selectedPositId;
    this->positName = positName;
    ui->label_positName->setText(positName);
    ui->procDate->setDate(QDate::currentDate());
}

Dialog_removeVacancy::~Dialog_removeVacancy()
{
    delete ui;
}

void Dialog_removeVacancy::accept()
{
    ui->buttonBox->setDisabled(true);
    int vacCount = ui->vacCount->value();
    QString proc_date = ui->procDate->date().toString("yyyy-MM-dd");
    QString queryText = "";
    for (int i=0; i < vacCount; i++)
    {
        queryText =  QString("select \"Myronenko_O\".delete_last_vacancy(%1, '%2');").arg(positId).arg(proc_date);
        db->executeQuery(queryText, "admin", this, i == vacCount-1 ? 2 : -1);
    }
    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
