#include "dialog_contractors.h"
#include "ui_dialog_contractors.h"

Dialog_contractors::Dialog_contractors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_contractors)
{
    ui->setupUi(this);
}

Dialog_contractors::~Dialog_contractors()
{
    delete ui;
}
