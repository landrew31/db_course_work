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
                             QDateEdit* date_edit = 0,
                             QWidget *parent = 0);
    static QSortFilterProxyModel* renew_programs(DB_setup* db, QTableView* table, QDateEdit* date_field);
    ~Dialog_programs();

private slots:
    void on_buttonBox_accepted();

    void on_clear_program_form_clicked();

signals:
    void programsChanged();

private:
    Ui::Dialog_programs *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QString *old_data;
    QDateEdit *date_edit;
};

#endif // DIALOG_PROGRAMS_H
