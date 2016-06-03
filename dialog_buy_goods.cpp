#include "dialog_buy_goods.h"
#include "ui_dialog_buy_goods.h"

Dialog_buy_goods::Dialog_buy_goods(DB_setup *db,
                                   QString mode,
                                   QTableView *table_contr,
                                   QTableView *table_good_types,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_buy_goods)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;
    this->table_contr = table_contr;
    this->table_good_types = table_good_types;

    this->old_move = new QString[2];
    renew_contr_comboBox();
    renew_doctype_comboBox();
    renew_goodtype_comboBox();
    renew_moves();
    renew_worker_comboBox();

    QString action = "";
    if (mode == "buy") {
        action = "Купити";
        this->setWindowTitle("Купівля товару");
        ui->doctype_box->setCurrentIndex(0);
    } else if (mode == "sale") {
        action = "Продати";
        this->setWindowTitle("Продаж товару");
        ui->doctype_box->setCurrentIndex(1);
        ui->buy_finally->setText("Продати");
        ui->add_new_good_type->setEnabled(false);
    };
    ui->quantity_dimension->clear();

    ui->doctype_box->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відмінити");
}

Dialog_buy_goods::~Dialog_buy_goods()
{
    delete ui;
}

void Dialog_buy_goods::renew_contr_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT contr_name FROM \"Lupa_A\".contractors ORDER BY contr_name;");
    qDebug() << "done" << endl;
    ui->contr_box->setModel(model);
    ui->contr_box->setCurrentIndex(-1);
}

void Dialog_buy_goods::renew_worker_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT per.per_surname || ' ' || per.per_name FROM (\"Myronenko_O\".person per JOIN \"Myronenko_O\".staff sta ON (sta.\"Id_person\" = per.\"Id_person\" AND sta.date_out is NULL) ) ORDER BY per_surname;");
    qDebug() << "done" << endl;
    ui->worker_box->setModel(model);
    ui->worker_box->setCurrentIndex(-1);
}

void Dialog_buy_goods::renew_doctype_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT doc_type_name FROM \"Lupa_A\".doc_types ORDER BY doc_type_name;");
    qDebug() << "done" << endl;
    ui->doctype_box->setModel(model);
    ui->doctype_box->setCurrentIndex(-1);
}

void Dialog_buy_goods::renew_goodtype_comboBox()
{
    QSqlQueryModel *model = db->getQueryModel("SELECT good_name FROM \"Lupa_A\".goods ORDER BY good_name;");
    qDebug() << "done" << endl;
    ui->good_type_box->setModel(model);
    ui->good_type_box->setCurrentIndex(-1);
}

void Dialog_buy_goods::renew_moves()
{
    int rows = good_names.length();
    ui->table->setColumnCount(2);
    ui->table->setRowCount(rows);
    for (int ridx = 0 ; ridx < rows ; ridx++ )
    {
        for (int cidx = 0 ; cidx < 2 ; cidx++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            if (cidx == 0){
                item->setText(good_names[ridx]);
            } else if (cidx == 1) {
                item->setText(quantities[ridx]);
            };
            ui->table->setItem(ridx,cidx,item);
        }
    }

    DB_setup::table_column_entire_width(ui->table);
}

void Dialog_buy_goods::on_add_new_contr_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "add",
                                                                    table_contr,
                                                                    0);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
    connect(dialog_contractors, SIGNAL(contractorsChanged()), this, SLOT(renew_contr_comboBox()));
}


void Dialog_buy_goods::on_add_new_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "add", table_good_types, 0);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
    connect(dialog_good_types, SIGNAL(goodtypesChanged()), this, SLOT(renew_goodtype_comboBox()));
}

void Dialog_buy_goods::on_good_type_box_currentTextChanged(const QString &arg1)
{
    QString good = ui->good_type_box->currentText();
    QSqlQueryModel *model = db->getQueryModel("SELECT item FROM \"Lupa_A\".goods WHERE good_name = '" + good + "';");
    QString item = model->record(0).value("item").toString();
    if (item == "Поштучний") {
        ui->quantity_dimension->setText("шт.");
    } else if (item == "Розсипний") {
        ui->quantity_dimension->setText("кг/л");
    };
}

void Dialog_buy_goods::on_table_pressed(const QModelIndex &index)
{
    ui->delete_move->setEnabled(true);
    ui->edit_move->setEnabled(true);
    ui->clear_move_buffer->setEnabled(true);
    ui->add_move_to_doc->setEnabled(false);
    int row = index.row();
    old_move[0] = index.sibling(row, 0).data().toString();
    old_move[1] = index.sibling(row, 1).data().toString();
    ui->good_type_box->setCurrentText(old_move[0]);
    ui->quantity->setText(old_move[1]);
    ui->move_buffer->setText(old_move[0]);
}

void Dialog_buy_goods::on_clear_move_buffer_clicked()
{
    ui->edit_move->setEnabled(false);
    ui->delete_move->setEnabled(false);
    ui->clear_move_buffer->setEnabled(false);
    ui->add_move_to_doc->setEnabled(true);
    ui->move_buffer->clear();
    ui->good_type_box->setCurrentIndex(-1);
    ui->quantity->clear();
}

void Dialog_buy_goods::on_edit_move_clicked()
{
    int i = good_names.indexOf(old_move[0]);
    QString new_name = ui->good_type_box->currentText();
    QString new_quantity = ui->quantity->text();
    QSqlQueryModel *model = db->getQueryModel("SELECT \"Id_goods\" as id FROM \"Lupa_A\".goods WHERE good_name = '" + new_name + "';");
    QString id = model->record(0).value("id").toString();
    qDebug() << id << endl;
    good_names.replace(i,new_name);
    quantities.replace(i,new_quantity);
    good_ids.replace(i,id);
    renew_moves();
    on_clear_move_buffer_clicked();
}

void Dialog_buy_goods::on_delete_move_clicked()
{
    int i = good_names.indexOf(old_move[0]);
    good_names.removeAt(i);
    quantities.removeAt(i);
    good_ids.removeAt(i);
    renew_moves();
    on_clear_move_buffer_clicked();
}

void Dialog_buy_goods::on_add_move_to_doc_clicked()
{
    QString new_name = ui->good_type_box->currentText();
    QString new_quantity = ui->quantity->text();
    good_names.append(new_name);
    QSqlQueryModel *model = db->getQueryModel("SELECT \"Id_goods\" as id FROM \"Lupa_A\".goods WHERE good_name = '" + new_name + "';");
    QString id = model->record(0).value("id").toString();
    qDebug() << id << "SELECT \"Id_goods\" FROM \"Lupa_A\".goods WHERE good_name = '" + new_name + "';" << endl;
    good_ids.append(id);
    quantities.append(new_quantity);
    renew_moves();
}


void Dialog_buy_goods::on_buy_finally_clicked()
{
    QString contr_name = ui->contr_box->currentText();
    QString stuff_name = ui->worker_box->currentText();
    QString doc_type = ui->doctype_box->currentText();
    int button;
    if (mode == "buy") {
        button = QMessageBox::question(this,
                 "Підтвердження закупки",
                 "Ви впевнені що хочете закупити дані товари? Перевірте коректність данних, можливості щось поміняти вже не буде!",
                 QMessageBox::Yes | QMessageBox::No);
    } else if (mode == "sale") {
        button = QMessageBox::question(this,
                 "Підтвердження продажу",
                 "Ви впевнені що хочете продати дані товари? Перевірте коректність данних, можливості щось поміняти вже не буде!",
                 QMessageBox::Yes | QMessageBox::No);
    }
    if (button == QMessageBox::Yes) {
        QString str_ids = "{";
        QString str_qua = "{";
        if (good_ids.length() == 1) {
            str_ids += good_ids[0] + "}";
            str_qua += quantities[0] + "}";
        } else if (good_ids.length() > 1) {
            for (int i=0; i < good_ids.length(); i++) {
                if (i < good_ids.length() - 1) {
                    str_ids += good_ids[i] + ",";
                    str_qua += quantities[i] + ",";
                } else if (i = good_ids.length() - 1) {
                    str_ids += good_ids[i] + "}";
                    str_qua += quantities[i] + "}";
                };
            };
         };
        qDebug() << "select \"Lupa_A\".buy_goods('" + contr_name + "','" + stuff_name + "','" + doc_type + "','" + str_ids + "','" + str_qua + "');" << endl;
        QString query = "";
        if (mode == "buy") {
            query = "select \"Lupa_A\".buy_goods('" + contr_name + "','" + stuff_name + "','" + doc_type + "','" + str_ids + "','" + str_qua + "');";
        } else if (mode == "sale") {
            query = "select \"Lupa_A\".buy_goods('" + contr_name + "','" + stuff_name + "','" + doc_type + "','" + str_ids + "','" + str_qua + "');";
        }
        bool executed = db->executeQuery(query, "operator", this, 0);
        if (executed) {
            emit added();
            this->close();
        }
    };
}
