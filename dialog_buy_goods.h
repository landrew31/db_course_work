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

namespace Ui {
class Dialog_buy_goods;
}

class Dialog_buy_goods : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_buy_goods(DB_setup* db=0,
                              QString mode="",
                              QWidget *parent = 0);
    ~Dialog_buy_goods();

private slots:
    void on_add_new_contr_clicked();
    void renew_contr_comboBox();
    void renew_worker_comboBox();
    void renew_doctype_comboBox();
    void renew_goodtype_comboBox();
    void renew_moves();

    void on_add_new_doctype_clicked();

    void on_add_new_good_type_clicked();

    void on_good_type_box_currentIndexChanged(const QString &arg1);

    void on_good_type_box_currentTextChanged(const QString &arg1);

    void on_table_pressed(const QModelIndex &index);

private:
    Ui::Dialog_buy_goods *ui;
    DB_setup *db;
    QString mode;
    QStringList good_names;
    QStringList quantities;
};

#endif // DIALOG_BUY_GOODS_H
