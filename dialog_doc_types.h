#ifndef DIALOG_DOC_TYPES_H
#define DIALOG_DOC_TYPES_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"

#include "ui_dialog_doc_types.h"

namespace Ui {
class Dialog_doc_types;
}

class Dialog_doc_types : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_doc_types(DB_setup* db=0,
                              QString mode="",
                              QTableView* table=0,
                              QString old_type=0,
                              QWidget *parent = 0);
    static void renew_doc_types(DB_setup* db, QTableView* table);
    ~Dialog_doc_types();

private slots:
    void on_clear_doc_type_form_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_doc_types *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QString old_type;
};

#endif // DIALOG_DOC_TYPES_H
