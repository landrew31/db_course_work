#include "dialog_good_actions_info.h"
#include "ui_dialog_good_actions_info.h"

Dialog_good_actions_info::Dialog_good_actions_info(DB_setup* db,
                                                   QTableView *table_goods,
                                                   QTableView *table_actions,
                                                   QString* good_data,
                                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_good_actions_info)
{
    ui->setupUi(this);
    this->db = db;
    this->table_goods = table_goods;
    this->table_actions = table_actions;
    this->good_data = good_data;
    this->old_action_data = new QString[4];
}

Dialog_good_actions_info::~Dialog_good_actions_info()
{
    delete ui;
}

void Dialog_good_actions_info::renew_good_actions(DB_setup* db, QString good, QTableView* table )
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_action_in_program('" + good + "');");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва акції"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Відсоток по акції"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Початок акції"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Кінець акції"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);

    DB_setup::table_column_entire_width(table);
}

void Dialog_good_actions_info::renew_actions_comboBox(DB_setup* db, QComboBox* box)
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions ORDER BY action_name;");
    box->setModel(model);
    box->setCurrentIndex(-1);
}

void Dialog_good_actions_info::on_tableView_actions_good_pressed(const QModelIndex &index)
{
    ui->update_action->setEnabled(true);
    ui->delete_action->setEnabled(true);
    ui->clear_action_buffer->setEnabled(true);
    int row = index.row();
    old_action_data[3] = index.sibling(row, 0).data().toString();
    QDate start = index.sibling(row, 2).data().toDate();
    old_action_data[0] = start.toString("yyyy-MM-dd");
    QDate stop = index.sibling(row, 3).data().toDate();
    old_action_data[1] = stop.toString("yyyy-MM-dd");
    int percent = index.sibling(row, 1).data().toInt();
    old_action_data[2] = QString::number(percent);
    ui->action_buffer->setText(old_action_data[3]);
}

void Dialog_good_actions_info::on_update_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "update", ui->tableView_actions_good, good_data);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
}

void Dialog_good_actions_info::on_add_new_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "add", table_actions, good_data);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Dialog_good_actions_info::on_add_action_to_good_clicked()
{
    QString action = ui->existing_actions_box->currentText();

    db->executeQuery(
            "select insert_new_action_in_program('" + good_data[0] + "','" + action + "');",
            "operator",
            this,
            0
    );
    renew_good_actions(db, good_data[0], ui->tableView_actions_good);
}

void Dialog_good_actions_info::on_clear_action_buffer_clicked()
{
    ui->update_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
    ui->clear_action_buffer->setEnabled(false);
    ui->action_buffer->clear();
}

void Dialog_good_actions_info::on_update_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "update", table_actions, old_action_data);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Dialog_good_actions_info::on_delete_action_clicked()
{
    QString name = old_action_data[3];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити акцію '" + name + "' з поточного товару?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "select \"Lupa_A\".delete_action_from_good('" + good_data[0] + "','" + name + "');",
                "operator",
                this,
                0
        );
        renew_good_actions(db, good_data[0], ui->tableView_actions_good);
    };
}
