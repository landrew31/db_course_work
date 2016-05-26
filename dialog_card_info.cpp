#include "dialog_card_info.h"
#include "ui_dialog_card_info.h"

Dialog_card_info::Dialog_card_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_card_info)
{
    ui->setupUi(this);
}

Dialog_card_info::~Dialog_card_info()
{
    delete ui;
}
