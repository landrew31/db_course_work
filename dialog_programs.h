#ifndef DIALOG_PROGRAMS_H
#define DIALOG_PROGRAMS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"

#include "ui_dialog_programs.h"


namespace Ui {
class Dialog_programs;
}

class Dialog_programs : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_programs(DB_setup* db=0, QString mode="",
                             QTableView *table=0,
                             QString* old_data = 0,
                             QWidget *parent = 0);
    static void renew_programs(DB_setup* db, QTableView* table);
    ~Dialog_programs();

private slots:
    void on_buttonBox_accepted();

    void on_clear_program_form_clicked();

private:
    Ui::Dialog_programs *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QString *old_data;
};

#endif // DIALOG_PROGRAMS_H