#include "dialog_createabstype.h"
#include "ui_dialog_createabstype.h"

Dialog_createAbsType::Dialog_createAbsType(DB_setup* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_createAbsType)
{
    ui->setupUi(this);
    this->db = db;
}

Dialog_createAbsType::~Dialog_createAbsType()
{
    delete ui;
}

void Dialog_createAbsType::accept()
{
    ui->buttonBox->setDisabled(true);
    QString name = ui->absName->text();
    if (name.length() == 0) {
        this->close();
        return;
    }
    QString descr = ui->absDescription->toPlainText();
    if (DEBUGMODE) qDebug() << "Dialog_createAbsType. Data to create: " << name << descr;
    QString queryText = QString(
        "insert into \"Myronenko_O\".absence_type (abs_name, abs_descr) "
            "values ('%1', '%2');").arg(name).arg(descr);
    db->executeQuery(queryText, "admin", this, 1);
    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
