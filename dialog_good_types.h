#ifndef DIALOG_GOOD_TYPES_H
#define DIALOG_GOOD_TYPES_H

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
class Dialog_good_types;
}

class Dialog_good_types : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_good_types(DB_setup* db=0,
                               QString mode="",
                               QTableView* table=0,
                               QString* old_data=0,
                               QWidget *parent = 0);

    static QSortFilterProxyModel* renew_good_types(DB_setup* db, QTableView* table );
    ~Dialog_good_types();

signals:
    void goodtypesChanged();

private slots:
    void on_clear_good_type_form_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_good_types *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QString *old_data;
};

#endif // DIALOG_GOOD_TYPES_H
