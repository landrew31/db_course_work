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
}

void Dialog_addStaff::updatePersSelect()
{

}
