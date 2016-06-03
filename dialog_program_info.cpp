#include "dialog_program_info.h"
#include "ui_dialog_program_info.h"

Dialog_program_info::Dialog_program_info(DB_setup* db,
                                         QTableView *table_programs,
                                         QTableView *table_actions,
                                         QString* program_data,
                                         QDateEdit* date_hist_program,
                                         QDateEdit* date_hist_action,
                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_program_info)
{
    ui->setupUi(this);
    this->db = db;
    this->table_programs = table_programs;
    this->table_actions = table_actions;
    this->program_data = program_data;
    this->date_hist_program = date_hist_program;
    this->date_hist_action = date_hist_action;
    this->old_action_data = new QString[4];
//    qDebug() << program_data[2] <<endl;
    renew_program_actions(db, this->program_data[2], ui->tableView_program_actions);
    renew_actions_comboBox();

    this->setWindowTitle("Редагування програми '" + program_data[2] + "'");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_program_info::~Dialog_program_info()
{
    delete ui;
}

void Dialog_program_info::renew_program_actions(DB_setup* db, QString program, QTableView* table )
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_action_in_program('" + program + "');");

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

void Dialog_program_info::renew_actions_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions WHERE day_stop >= date_trunc('day',now()) ORDER BY action_name;");
    ui->existing_actions_box->setModel(model);
    ui->existing_actions_box->setCurrentIndex(-1);
}

void Dialog_program_info::on_update_program_clicked()
{
    Dialog_programs* dialog_programs = new Dialog_programs(db, "update", table_programs, program_data, date_hist_program);
    dialog_programs->setModal(true);
    dialog_programs->show();
}

void Dialog_program_info::on_add_new_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "add", table_actions, program_data, date_hist_action);
    dialog_actions->setModal(true);
    dialog_actions->show();
    connect(dialog_actions, SIGNAL(actionsChanged()), this, SLOT(renew_actions_comboBox()));
}

void Dialog_program_info::on_add_action_to_program_clicked()
{
    QString action = ui->existing_actions_box->currentText();

    db->executeQuery(
            "select insert_new_action_in_program('" + program_data[2] + "','" + action + "');",
            db->getUser(),
            this,
            1
    );
    renew_program_actions(db, program_data[2], ui->tableView_program_actions);
}

void Dialog_program_info::on_tableView_program_actions_pressed(const QModelIndex &index)
{
    ui->update_action->setEnabled(true);
    ui->delete_action->setEnabled(true);
    ui->clear_action_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    QDate start = index.sibling(row, 2).data().toDate();
    QString str_start = start.toString("yyyy-MM-dd");
    QDate stop = index.sibling(row, 3).data().toDate();
    QString str_stop = stop.toString("yyyy-MM-dd");
    int percent = index.sibling(row, 1).data().toInt();
    QString str_percent = QString::number(percent);
    old_action_data[0] = str_start;
    old_action_data[1] = str_stop;
    old_action_data[2] = str_percent;
    old_action_data[3] = name;
    ui->action_buffer->setText(name);
}

void Dialog_program_info::on_clear_action_buffer_clicked()
{
    ui->update_action->setEnabled(false);
    ui->delete_action->setEnabled(false);
    ui->clear_action_buffer->setEnabled(false);
    ui->action_buffer->clear();
}

void Dialog_program_info::on_update_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "update", table_actions, old_action_data, date_hist_action);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Dialog_program_info::on_delete_action_clicked()
{
    QString name = old_action_data[3];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити акцію '" + name + "' з поточної програми?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "select \"Lupa_A\".delete_action_from_program('" + program_data[2] + "','" + name + "');",
                "operator",
                this,
                0
        );
        Dialog_program_info::renew_program_actions(db, program_data[2], ui->tableView_program_actions);
    };
}


