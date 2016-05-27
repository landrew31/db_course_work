/* RENEW VIEWS BLOCK */
#include "db_setup.h"
#include <QTableView>

void renew_programs(DB_setup* db, QTableView* table)
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_not_finished_actions_on_programs;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва програми"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Доступні зараз акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
//    ui->action_on_program->setCurrentIndex(-1);
}

void renew_cards(DB_setup* db, QTableView* table)
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_cards;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Контрагент"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Доступні зараз програми"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Доступні зараз акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
    table->resizeColumnToContents(2);
//    ui->contr_for_card->setCurrentIndex(-1);
//    ui->program_on_card->setCurrentIndex(-1);
//    ui->single_action_on_card->setCurrentIndex(-1);
}

/* END RENEW VIEWS BLOCK */