#include "dialog_createskill.h"
#include "ui_dialog_createskill.h"

Dialog_createSkill::Dialog_createSkill(DB_setup *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_createSkill)
{
    ui->setupUi(this);
    this->db = db;
}

Dialog_createSkill::~Dialog_createSkill()
{
    delete ui;
}

void Dialog_createSkill::accept()
{
    QString name = ui->lineEdit_name->text();
    if (name.length() == 0) {
        this->close();
        return;
    }
    QString descr = ui->textEdit_descr->toPlainText();
    if (DEBUGMODE) qDebug() << "Dialog_createSkill. Data to create: " << name << descr;
    QString queryText =
        "insert into \"Myronenko_O\".skills (skill_name, skill_description)"
            "values ('" + name + "', '" + descr + "'"
        ");";
    db->executeQuery(queryText, "admin", this, 1);
    this->accepted();
    this->close();
}
