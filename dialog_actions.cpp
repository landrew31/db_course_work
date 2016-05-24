#include "dialog_actions.h"
#include "ui_dialog_actions.h"

Dialog_actions::Dialog_actions(DB_setup *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_actions)
{
    ui->setupUi(this);
    this->db = db;
}

Dialog_actions::~Dialog_actions()
{
    delete ui;
}
