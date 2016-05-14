#include "dialogentry.h"
#include "ui_dialogentry.h"
#include "functions.cpp"


DialogEntry::DialogEntry(DB_setup *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEntry)
{
    ui->setupUi(this);
    this->db = db;
    sale_dep_users.append("admin");
    sale_dep_users.append("operator");
    hr_dep_users.append("admin");
    hr_dep_users.append("hr_operator");
    all_departments.append("Відділ кадрів");
    all_departments.append("Відділ продаж");

    ui->department_select->addItems(all_departments);
    ui->department_select->setCurrentIndex(0);
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
    ui->enter_button->setEnabled(false);
    QString choseDep = ui->department_select->currentText();
    bool connected = db->connect_to_db(this);
    if (connected) {
        QStringList chosenDepartmentUsers;
        if (choseDep == "Відділ продаж") {
            chosenDepartmentUsers = sale_dep_users;
        } else if (choseDep == "Відділ кадрів") {
            chosenDepartmentUsers = hr_dep_users;
        }
        if (inQStringList(db->getUser(), chosenDepartmentUsers)) {
            if (choseDep == "Відділ продаж") {
                MainWindow* mainWindow = new MainWindow(db);
                this->hide();
                mainWindow->show();
                return;
            }
            if (choseDep == "Відділ кадрів") {
                HR_department* hr_department = new HR_department(db);
                this->hide();
                hr_department->show();
                return;
            }
        };
        QMessageBox::about(this, "Помилка", "У Вас немає доступу до цього відділу.");
    };
    ui->enter_button->setEnabled(true);
}
