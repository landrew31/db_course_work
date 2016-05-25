#ifndef DIALOG_CONTRACTORS_H
#define DIALOG_CONTRACTORS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"

#include "ui_dialog_contractors.h"

namespace Ui {
class Dialog_contractors;
}

class Dialog_contractors : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_contractors(DB_setup* db=0,
                                QString mode="",
                                QTableView *table = 0,
                                QComboBox *combobox = 0,
                                QString* old_data=0,
                                QWidget *parent = 0);
    static void renew_contractors(DB_setup* db, QTableView* table);
    static void renew_contr_on_card_comboBox(DB_setup* db, QComboBox* box);

    ~Dialog_contractors();

private slots:
    void on_is_individual_clicked(bool checked);

    void on_is_entity_clicked(bool checked);

    void on_clear_contr_form_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_contractors *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QComboBox *combobox;
    QString *old_data;
};

#endif // DIALOG_CONTRACTORS_H
