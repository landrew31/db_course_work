#ifndef DIALOG_ACTIONS_H
#define DIALOG_ACTIONS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"

#include "ui_dialog_actions.h"



namespace Ui {
class Dialog_actions;
}

class Dialog_actions : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_actions(DB_setup* db=0, QString mode="",
                            QTableView *table=0,
                            QString* old_data = 0,
                            QDateEdit* date_edit = 0,
                            QWidget *parent = 0);
    static QSortFilterProxyModel* renew_actions(DB_setup* db, QTableView* table, QDateEdit* date_field);
    ~Dialog_actions();

signals:
    void actionsChanged();

private slots:
    void on_buttonBox_accepted();

    void on_clear_action_form_clicked();

private:
    Ui::Dialog_actions *ui;
    DB_setup *db;
    QString mode;
    QTableView *table;
    QString *old_data;
    QDateEdit *date_edit;
};

#endif // DIALOG_ACTIONS_H
