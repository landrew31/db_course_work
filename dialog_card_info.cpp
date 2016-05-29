#include "dialog_card_info.h"
#include "ui_dialog_card_info.h"

Dialog_card_info::Dialog_card_info(DB_setup* db,
                                   QTableView *table_contr,
                                   QTableView *table_programs,
                                   QTableView *table_actions,
                                   QString* contr_data,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_card_info)
{
    ui->setupUi(this);
    this->db = db;
    this->table_contr = table_contr;
    this->table_programs = table_programs;
    this->table_actions = table_actions;
    this->contr_data = contr_data;
    this->old_program_data = new QString[3];

    renew_contr_programs(db, this->contr_data[0], ui->tableView_contr_programs);
    renew_programs_comboBox();

    this->setWindowTitle("Редагування картки контрагента '" + contr_data[2] + "'");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");

}

Dialog_card_info::~Dialog_card_info()
{
    delete ui;
}

void Dialog_card_info::renew_contr_programs(DB_setup* db, QString contr, QTableView* table)
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".show_program_in_card('" + contr + "');");

    qDebug() << "one" << endl;

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Назва програми"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Початок програми"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Кінець програми"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);
    table->setSortingEnabled(true);
    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);
    table->resizeColumnToContents(2);

    DB_setup::table_column_entire_width(table);
}

void Dialog_card_info::renew_programs_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT program_name FROM \"Lupa_A\".programs ORDER BY program_name;");
    qDebug() << "done" << endl;
    ui->existing_programs_box->setModel(model);
    ui->existing_programs_box->setCurrentIndex(-1);
}


void Dialog_card_info::on_update_contr_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "update",
                                                                    table_contr,
                                                                    contr_data);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
}

void Dialog_card_info::on_add_new_program_clicked()
{
    Dialog_programs* dialog_programs = new Dialog_programs(db, "add", table_programs, old_program_data);
    dialog_programs->setModal(true);
    dialog_programs->show();
    connect(dialog_programs, SIGNAL(programsChanged()), this, SLOT(renew_programs_comboBox()));
}

void Dialog_card_info::on_tableView_contr_programs_pressed(const QModelIndex &index)
{
    ui->update_program_button->setEnabled(true);
    ui->delete_program_button->setEnabled(true);
    ui->action_on_program_info->setEnabled(true);
    ui->clear_program_buffer->setEnabled(true);
    int row = index.row();
    QString name = index.sibling(row, 0).data().toString();
    QDate start = index.sibling(row, 1).data().toDate();
    QString str_start = start.toString("yyyy-MM-dd");
    QDate stop = index.sibling(row, 2).data().toDate();
    QString str_stop = stop.toString("yyyy-MM-dd");
    old_program_data[0] = str_start;
    old_program_data[1] = str_stop;
    old_program_data[2] = name;
    ui->program_buffer->setText(name);
}



void Dialog_card_info::on_add_program_on_card_clicked()
{
    QString program = ui->existing_programs_box->currentText();

    db->executeQuery(
            "select insert_new_program_in_card('" + contr_data[0] + "','" + program + "');",
            "operator",
            this,
            0
    );
    renew_contr_programs(db, this->contr_data[0], ui->tableView_contr_programs);

}

void Dialog_card_info::on_clear_program_buffer_clicked()
{
    ui->update_program_button->setEnabled(false);
    ui->delete_program_button->setEnabled(false);
    ui->clear_program_buffer->setEnabled(false);
    ui->action_on_program_info->setEnabled(false);
    ui->program_buffer->clear();
}

void Dialog_card_info::on_update_program_button_clicked()
{
    Dialog_programs* dialog_programs = new Dialog_programs(db, "update", ui->tableView_contr_programs, old_program_data);
    dialog_programs->setModal(true);
    dialog_programs->show();
}

void Dialog_card_info::on_action_on_program_info_clicked()
{
    Dialog_program_info* program_info = new Dialog_program_info(db,
                                                                table_programs,
                                                                table_actions,
                                                                old_program_data);
    program_info->setModal(true);
    program_info->show();
}

void Dialog_card_info::on_delete_program_button_clicked()
{
    QString name = old_program_data[2];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити програму '" + name + "' з картки контрагента?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "select \"Lupa_A\".delete_program_from_card('" + contr_data[0] + "','" + name + "');",
                "operator",
                this,
                0
        );
        renew_contr_programs(db, this->contr_data[0], ui->tableView_contr_programs);
    };
}
