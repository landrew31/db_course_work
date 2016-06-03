#ifndef DIALOGENTRY_H
#define DIALOGENTRY_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "db_setup.h"
#include "sale_department.h"
#include "hr_department.h"
#include "functions.h"

#define UNSECURE true
#define UNSECURE_DEP 1

namespace Ui {
    class DialogEntry;
}

class DialogEntry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEntry(DB_setup* db = 0, QWidget *parent = 0);
    ~DialogEntry();

private slots:
    void on_username_field_textChanged();
    void on_password_field_textChanged();
    void on_cancel_entry_button_clicked();
    void on_enter_button_clicked();

private:
    Ui::DialogEntry *ui;
    DB_setup *db;
    QStringList sale_dep_users, hr_dep_users, all_departments;
};

#endif // DIALOGENTRY_H
