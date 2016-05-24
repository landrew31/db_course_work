#include "dialog_editpersinfo.h"


Dialog_editPersInfo::Dialog_editPersInfo(DB_setup *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUi_editPersInfo)
{
    ui->setupUi(this);
    this->db = db;
}

Dialog_editPersInfo::~Dialog_editPersInfo()
{
    delete ui;
}
