#include "dialogentry.h"
#include "ui_dialogentry.h"
#include <QMessageBox>

DialogEntry::DialogEntry(DB_setup *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEntry)
{
    ui->setupUi(this);
    this->db = db;
    ui->username_field->setFocus();
}

DialogEntry::~DialogEntry()
{
    delete ui;
}

// enter user
void DialogEntry::on_username_field_textChanged()
{
    db->setUser(ui->username_field->text());
}

// enter password
void DialogEntry::on_password_field_textChanged()
{
    db->setPassword(ui->password_field->text());
}

//cancel button
void DialogEntry::on_cancel_entry_button_clicked()
{
    this->close();
}

// enter button
void DialogEntry::on_enter_button_clicked()
{
    ui->enter_button->setEnabled(true);
    bool connected = db->connect_to_db(this);
    if (connected) {
        ui->enter_button->setEnabled(false);
        MainWindow* mainWindow = new MainWindow(db);
        this->hide();
        mainWindow->show();
    }
}
