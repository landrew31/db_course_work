#include "dialog_buy_goods.h"
#include "ui_dialog_buy_goods.h"

Dialog_buy_goods::Dialog_buy_goods(DB_setup *db,
                                   QString mode,
                                   QTableView *table_contr,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_buy_goods)
{
    ui->setupUi(this);
    this->db = db;
    this->mode = mode;

    QString action = "";
    if (mode == "buy") {
        action = "Купити";
        this->setWindowTitle("Купівля товару");
    }
}

Dialog_buy_goods::~Dialog_buy_goods()
{
    delete ui;
}

void Dialog_buy_goods::renew_moves_on_doc(DB_setup *db, ){
    QSqlQueryModel *model = db->
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
    QSqlQueryModel *model = db->getQueryModel("SELECT per.per_surname || ' ' || per.per_name FROM (\"Myronenko_O\".persons per JOIN \"Myronenko_O\".staff sta ON (sta.\"Id_person\" = per.\"Id_person\") ) ORDER BY per_surname;");
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
    ui->doctype_box->setModel(model);
    ui->doctype_box->setCurrentIndex(-1);
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
}

void Dialog_buy_goods::on_add_new_contr_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "add",
                                                                    table_contr,
                                                                    0);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
    connect(dialog_contractors, SIGNAL(contractorsChanged()), this, SLOT(renew_contr_comboBox());
}

void Dialog_buy_goods::on_add_new_doctype_clicked()
{
    Dialog_doc_types* dialog_doc_type = new Dialog_doc_types(db, "add", table_doc_types, 0);
    dialog_doc_type->setModal(true);
    dialog_doc_type->show();
    connect(dialog_doc_type, SIGNAL(doctypesChanged()), this, SLOT(renew_doctype_comboBox());
}

void Dialog_buy_goods::on_add_new_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "add", table_good_types, 0);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
    connect(dialog_good_types, SIGNAL(goodtypesChanged()), this, SLOT(renew_goodtype_comboBox());
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
    old_move[1] = index.sibling(row, 2).data().toString();
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
    good_names.replace(i,new_name);
    quantities.replace(i,new_quantity);
    renew_moves();
    on_clear_move_buffer_clicked();
}

void Dialog_buy_goods::on_delete_move_clicked()
{
    int i = good_names.indexOf(old_move[0]);
    good_names.removeAt(i);
    quantities.removeAt(i);
    renew_moves();
    on_clear_move_buffer_clicked();
}

void Dialog_buy_goods::on_add_move_to_doc_clicked()
{
    QString new_name = ui->good_type_box->currentText();
    QString new_quantity = ui->quantity->text();
    good_names.append(new_name);
    quantities.append(new_quantity);
    renew_moves();
}

void Dialog_buy_goods::on_pushButton_clicked()
{

}
