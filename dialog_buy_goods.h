#ifndef DIALOG_BUY_GOODS_H
#define DIALOG_BUY_GOODS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include "db_setup.h"

#include "ui_dialog_buy_goods.h"

#include "dialog_contractors.h"
#include "dialog_good_types.h"

namespace Ui {
class Dialog_buy_goods;
}

class Dialog_buy_goods : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_buy_goods(DB_setup* db=0,
                              QString mode="",
                              QTableView* table_contr=0,
                              QTableView* table_good_types=0,
                              QWidget *parent = 0);
    ~Dialog_buy_goods();

private slots:
    void on_add_new_contr_clicked();
    void renew_contr_comboBox();
    void renew_worker_comboBox();
    void renew_doctype_comboBox();
    void renew_goodtype_comboBox();
    void renew_moves();


    void on_add_new_good_type_clicked();

    void on_good_type_box_currentTextChanged(const QString &arg1);

    void on_table_pressed(const QModelIndex &index);

    void on_clear_move_buffer_clicked();
    
    void on_edit_move_clicked();
    
    void on_delete_move_clicked();
    
    void on_add_move_to_doc_clicked();

    
    void on_buy_finally_clicked();

signals:
    void added();


private:
    Ui::Dialog_buy_goods *ui;
    DB_setup *db;
    QString mode;
    QTableView *table_contr;
    QTableView *table_good_types;
    QStringList good_names;
    QStringList quantities;
    QStringList good_ids;
    QString *old_move;
};

#endif // DIALOG_BUY_GOODS_H
