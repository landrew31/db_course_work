#include "dialogentry.h"
#include "ui_dialogentry.h"
#include <QMessageBox>

DialogEntry::DialogEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEntry)
{
    ui->setupUi(this);
}

DialogEntry::~DialogEntry()
{
    delete ui;
}

// enter user
void DialogEntry::on_username_field_textChanged(const QString &arg1)
{
    user = ui->username_field->text();
}

// enter password
void DialogEntry::on_password_field_textChanged(const QString &arg1)
{
    password = ui->password_field->text();
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
    connected = connect_to_db();
    if (connected) {
        ui->enter_button->setEnabled(false);
        MainWindow* mainWindow = new MainWindow();
        mainWindow->setDB(user, password);
        this->hide();
        mainWindow->show();
    }
}

bool DialogEntry::connect_to_db(){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("52.24.64.65");
    db.setPort(5432);
    db.setDatabaseName("db_work");
    db.setUserName(user);
    db.setPassword(password);

    bool connectioncheck = db.open();
    connected = connectioncheck;
    if (connectioncheck == true){
        qDebug() << "Connection to database established." << endl;
    } else {
        qDebug() << "Error for database " << db.databaseName() << " :" << db.lastError().text() << endl;
        QMessageBox::about(this, "Помилка", "Не вдалося увійти. Перевірте, будь ласка, ім'я та пароль.");
    }
    return connectioncheck;
}

bool DialogEntry::getConnected(){
    return connected;
}

