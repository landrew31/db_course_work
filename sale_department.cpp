#include "sale_department.h"
#include "dialogentry.h"
#include <QDebug>
#include "QtPrintSupport/QPrinter"
#include <QtPrintSupport/QPrintDialog>

Sale_department::Sale_department(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sale_department)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;
    ui->tableView_goods_left->hide();
    ui->good_price_search->setValidator( new QDoubleValidator(0, 100, 2, this) );

    ui->date_hist_actions->setDate( QDate::currentDate());
    ui->date_hist_programs->setDate(QDate::currentDate());
    proxy_actions = Dialog_actions::renew_actions(db, ui->tableView_actions, ui->date_hist_actions);
    proxy_contr = Dialog_contractors::renew_contractors(db, ui->tableView_contractors);
    proxy_programs = Dialog_programs::renew_programs(db, ui->tableView_programs, ui->date_hist_programs);
   proxy_goods = Dialog_good_types::renew_good_types(db, ui->tableView_good_types);
    renew_documents();
    renew_left_goods();
}

Sale_department::~Sale_department()
{
    delete ui;
}

/* START ACTIONS TAB SLOTS BLOCK */

void Sale_department::on_add_action_button_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "add", ui->tableView_actions, old_action_data, ui->date_hist_actions);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_tableView_actions_pressed(const QModelIndex &index)
{
    ui->update_action->setEnabled(true);
    ui->stop_action->setEnabled(true);
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

void Sale_department::on_clear_action_buffer_clicked()
{
    ui->update_action->setEnabled(false);
    ui->stop_action->setEnabled(false);
    ui->clear_action_buffer->setEnabled(false);
    ui->action_buffer->clear();
}

void Sale_department::on_update_action_clicked()
{
    Dialog_actions* dialog_actions = new Dialog_actions(db, "update", ui->tableView_actions, old_action_data, ui->date_hist_actions);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_stop_action_clicked()
{

    QString name = old_action_data[3];
    int button = QMessageBox::question(this,
                 "Підтвердження закриття",
                 "Ви впевнені що хочете закрити акцію '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        qDebug() << "UPDATE \"Lupa_A\".actions SET (day_stop) = (date_trunc('day',now())) WHERE action_name = '" + name + "';" << endl;

        db->executeQuery(
                "UPDATE \"Lupa_A\".actions SET (day_stop) = (date_trunc('day',now())) WHERE action_name = '" + name + "';",
                db->getUser(),
                this,
                2
        );
        proxy_actions = Dialog_actions::renew_actions(db, ui->tableView_actions,  ui->date_hist_actions);
    };
}
/* END ACTIONS TAB SLOTS BLOCK */

/* START CONTRACTORS TAB SLOTS BLOCK */

void Sale_department::on_add_contractor_button_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "add",
                                                                    ui->tableView_contractors,
                                                                    old_contr_data);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
}

void Sale_department::on_tableView_contractors_pressed(const QModelIndex &index)
{
    ui->update_contractor->setEnabled(true);
//    ui->delete_contr->setEnabled(true);
    ui->clear_contractor_buffer->setEnabled(true);
    int row = index.row();
    old_contr_data[0] = index.sibling(row, 0).data().toString();
    old_contr_data[3] = index.sibling(row, 1).data().toString();
    old_contr_data[4] = index.sibling(row, 2).data().toString();
    QDate birth = index.sibling(row, 3).data().toDate();
    old_contr_data[1] = birth.toString("yyyy-MM-dd");
    old_contr_data[2] = index.sibling(row, 4).data().toString();
    if (old_contr_data[1] != "") {
        ui->card_info->setEnabled(true);
    } else if (old_contr_data[2] != "") {
        ui->card_info->setEnabled(false);
    }
    ui->contractor_buffer->setText(old_contr_data[0]);
}

void Sale_department::on_clear_contractor_buffer_clicked()
{
    ui->update_contractor->setEnabled(false);
    ui->delete_contr->setEnabled(false);
    ui->clear_contractor_buffer->setEnabled(false);
    ui->card_info->setEnabled(false);
    ui->contractor_buffer->clear();
}

void Sale_department::on_update_contractor_clicked()
{
    Dialog_contractors* dialog_contractors = new Dialog_contractors(db, "update",
                                                                    ui->tableView_contractors,
                                                                    old_contr_data);
    dialog_contractors->setModal(true);
    dialog_contractors->show();
}

void Sale_department::on_card_info_clicked()
{
    Dialog_card_info * card_info = new Dialog_card_info(db,
                                                        ui->tableView_contractors,
                                                        ui->tableView_programs,
                                                        ui->tableView_actions,
                                                        old_contr_data,
                                                        ui->date_hist_programs,
                                                        ui->date_hist_actions
                                                      );
    card_info->setModal(true);
    card_info->show();
}

void Sale_department::on_delete_contr_clicked()
{
    QString name = old_contr_data[0];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити контрагента '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".contractors where contr_name = '" + name +"';",
                "operator",
                this,
                3
        );
        proxy_contr = Dialog_contractors::renew_contractors(db, ui->tableView_contractors);
    };
}

/* END CONTRACTORS TAB SLOTS BLOCK */

/* START PROGRAMS TAB SLOTS BLOCK */

void Sale_department::on_add_program_button_clicked()
{
    Dialog_programs* dialog_actions = new Dialog_programs(db, "add", ui->tableView_programs, old_program_data, ui->date_hist_programs);
    dialog_actions->setModal(true);
    dialog_actions->show();
}

void Sale_department::on_tableView_programs_pressed(const QModelIndex &index)
{
    ui->update_program_button->setEnabled(true);
    ui->stop_program_button->setEnabled(true);
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

void Sale_department::on_clear_program_buffer_clicked()
{
    ui->update_program_button->setEnabled(false);
    ui->stop_program_button->setEnabled(false);
    ui->clear_program_buffer->setEnabled(false);
    ui->action_on_program_info->setEnabled(false);
    ui->program_buffer->clear();
}

void Sale_department::on_update_program_button_clicked()
{
    Dialog_programs* dialog_programs = new Dialog_programs(db, "update", ui->tableView_programs, old_program_data, ui->date_hist_programs);
    dialog_programs->setModal(true);
    dialog_programs->show();

}

void Sale_department::on_stop_program_button_clicked()
{
    QString name = old_program_data[2];
    int button = QMessageBox::question(this,
                 "Підтвердження закриття",
                 "Ви впевнені що хочете закрити програму '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        qDebug() << "UPDATE \"Lupa_A\".programs SET (day_stop) = (date_trunc('day',now())) WHERE program_name = '" + name + "';" << endl;

        db->executeQuery(
                "UPDATE \"Lupa_A\".programs SET (day_stop) = (date_trunc('day',now())) WHERE program_name = '" + name + "';",
                db->getUser(),
                this,
                2
        );
        proxy_programs = Dialog_programs::renew_programs(db, ui->tableView_programs, ui->date_hist_programs);
    };
}

void Sale_department::on_action_on_program_info_clicked()
{
    Dialog_program_info* program_info = new Dialog_program_info(db,
                                                                ui->tableView_programs,
                                                                ui->tableView_actions,
                                                                old_program_data,
                                                                ui->date_hist_programs,
                                                                ui->date_hist_actions);
    program_info->setModal(true);
    program_info->show();
}

/* END PROGRAMS TAB SLOTS BLOCK */

/* START GOOD TYPES SLOTS BLOCK */

void Sale_department::on_add_new_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "add", ui->tableView_good_types, old_good_data);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
}

void Sale_department::on_tableView_good_types_pressed(const QModelIndex &index)
{
    ui->update_good_type->setEnabled(true);
//    ui->delete_good_type->setEnabled(true);
    ui->clear_good_type_buffer->setEnabled(true);
    ui->action_on_good_info->setEnabled(true);
    int row = index.row();
    old_good_data[0] = index.sibling(row, 0).data().toString(); // name
    old_good_data[3] = index.sibling(row, 1).data().toString(); // price
    old_good_data[1] = index.sibling(row, 2).data().toString(); // term
    old_good_data[2] = index.sibling(row, 3).data().toString(); // item
    ui->good_type_buffer->setText(old_good_data[0]);
}

void Sale_department::on_update_good_type_clicked()
{
    Dialog_good_types* dialog_good_types = new Dialog_good_types(db, "update", ui->tableView_good_types, old_good_data);
    dialog_good_types->setModal(true);
    dialog_good_types->show();
}

void Sale_department::on_clear_good_type_buffer_clicked()
{
    ui->update_good_type->setEnabled(false);
    ui->delete_good_type->setEnabled(false);
    ui->clear_good_type_buffer->setEnabled(false);
    ui->action_on_good_info->setEnabled(false);
    ui->good_type_buffer->clear();
}

void Sale_department::on_delete_good_type_clicked()
{
    QString name = old_good_data[0];
    int button = QMessageBox::question(this,
                 "Підтвердження видалення",
                 "Ви впевнені що хочете видалити вид товару '" + name + "'?",
                 QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes) {
        db->executeQuery(
                "delete from \"Lupa_A\".goods where good_name = '" + name + "';",
                "operator",
                this,
                3
        );
        proxy_goods = Dialog_good_types::renew_good_types(db, ui->tableView_good_types);
    };
}

void Sale_department::on_action_on_good_info_clicked()
{
    Dialog_good_actions_info* good_actions_info = new Dialog_good_actions_info(db,
                                                                ui->tableView_good_types,
                                                                ui->tableView_actions,
                                                                old_good_data,
                                                                ui->date_hist_actions);
    good_actions_info->setModal(true);
    good_actions_info->show();
}

/* END GOOD TYPES SLOTS BLOCK */

/* START MOVES SLOTS BLOCK */

void Sale_department::renew_documents()
{
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".documents;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Працівник"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Дата"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Тип документа"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Сума"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Контрагент"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    ui->tableView_moves->setModel(proxyModel);
    ui->tableView_moves->setSortingEnabled(true);
    DB_setup::table_column_entire_width(ui->tableView_moves);
}

void Sale_department::renew_left_goods()
{
    qDebug() << "select * from \"Lupa_A\".left_goods;" << endl;
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".left_goods;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Товар"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ціна"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Термін придатності (дні)"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Залишок на складі"));
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    ui->tableView_goods_left->setModel(proxyModel);
    ui->tableView_goods_left->setSortingEnabled(true);
    DB_setup::table_column_entire_width(ui->tableView_goods_left);
}

void Sale_department::on_buy_goods_clicked()
{
    Dialog_buy_goods *buy_goods = new Dialog_buy_goods(db,
                                                       "buy",
                                                       ui->tableView_contractors,
                                                       ui->tableView_good_types);
    buy_goods->setModal(true);
    buy_goods->show();
    connect(buy_goods, SIGNAL(added()), this, SLOT(renew_documents()));
    connect(buy_goods, SIGNAL(added()), this, SLOT(renew_left_goods()));
}

void Sale_department::on_see_goods_left_clicked()
{
    ui->see_docs->setEnabled(true);
    ui->see_goods_left->setEnabled(false);
    ui->tableView_moves->hide();
    ui->tableView_goods_left->show();
}

void Sale_department::on_see_docs_clicked()
{
    ui->see_docs->setEnabled(false);
    ui->see_goods_left->setEnabled(true);
    ui->tableView_goods_left->hide();
    ui->tableView_moves->show();
}

void Sale_department::on_clear_doc_buffer_clicked()
{
    ui->print->setEnabled(false);
    ui->clear_doc_buffer->setEnabled(false);
    ui->doc_buffer->clear();
}

void Sale_department::on_tableView_moves_pressed(const QModelIndex &index)
{
    ui->print->setEnabled(true);
    ui->clear_doc_buffer->setEnabled(true);
    int row = index.row();
    old_doc = index.sibling(row, 1).data().toString(); // name
    ui->doc_buffer->setText(old_doc);
}

void Sale_department::on_sale_goods_clicked()
{
    Dialog_buy_goods *sale_goods = new Dialog_buy_goods(db,
                                                       "sale",
                                                       ui->tableView_contractors,
                                                       ui->tableView_good_types);
    sale_goods->setModal(true);
    sale_goods->show();
    connect(sale_goods, SIGNAL(added()), this, SLOT(renew_documents()));
    connect(sale_goods, SIGNAL(added()), this, SLOT(renew_left_goods()));
}

void Sale_department::on_print_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    QSqlQueryModel *model_for_id = db->getQueryModel("select * from \"Lupa_A\".documentation where (SELECT date_trunc('second',doc_date)) = '" + old_doc + "';");
    qDebug() << "select * from \"Lupa_A\".documentation where (SELECT date_trunc('second',doc_date)) = '" + old_doc + "';" << endl;
    QString doc_id = model_for_id->data(model_for_id->index(0,0)).toString();

    QSqlQueryModel *model_doc_data = db->getQueryModel("SELECT doc.* FROM (\"Lupa_A\".documents doc JOIN \"Lupa_A\".documentation docum ON ( doc.doc_date = docum.doc_date and docum.\"Id_doc\" = " + doc_id + "));");
    qDebug() << "SELECT doc.* FROM (\"Lupa_A\".documents doc JOIN \"Lupa_A\".documentation docum ON ( doc.doc_date = docum.doc_date and docum.\"Id_doc\" = " + doc_id + "));" << endl;
    QString staff_name = model_doc_data->data(model_doc_data->index(0,0)).toString();
    QString date = model_doc_data->data(model_doc_data->index(0,1)).toString();
    QString doc_type = model_doc_data->data(model_doc_data->index(0,2)).toString();
    QString total_money = model_doc_data->data(model_doc_data->index(0,3)).toString();
    QString contr_name = model_doc_data->data(model_doc_data->index(0,4)).toString();

    qDebug() << doc_id << endl;
    QSqlQueryModel *model = db->getQueryModel("select * from \"Lupa_A\".moves_on_doc(" + doc_id + ");");
    qDebug() << "select * from \"Lupa_A\".moves_on_doc(" + doc_id + ");" << endl;

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Товар"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ціна"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Форма"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Термін придатності (дні)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Кількість"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Загальна сума"));
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    out << "<html>\n" << "<head>\n" << "<meta Content=\"Text/html; charset=utf-8\">\n" <<
           QString("<title>%1</title>\n").arg("Report") <<
           "</head>\n"
           "<body bgcolor = #ffffff link=#5000A0>\n" <<
           QString("<h3 align=center>%1</h3>\n").arg(doc_type) <<
           "<br />\n"
           "<br />\n"
           "<br />\n" <<
           QString("<p>Контрагент: <b>%1</b></p>\n").arg(contr_name) <<
           QString("<p>Працівник: <b>%1</b></p>\n").arg(staff_name) <<
           QString("<p>Дата: <b>%1</b></p>\n").arg(date) <<
           QString("<h6>Загальна сума: <b>%1</b></h6>\n").arg(total_money) <<
           "<br />\n"
           "<br />\n"
           "<table border = 1 cellspacing=0 cellpadding=2>\n";

    out<<"<thead><tr bgcolo=#f0f0f0>";
    for( int column = 0; column < columnCount; column++)
        out << QString("<th>%1</th>").arg(model->headerData(column,Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++ ) {
        out << "<tr>";
        for ( int column = 0; column < columnCount; column++){
            QString data = model->data(model->index(row,column)).toString().simplified();
            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
        out << "</tr>\n";
    }
    out << "</table>\n""</body>\n""</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);
    qDebug() << strStream << endl;
    QPrinter printer;
    QString file_name = QDir::currentPath();
    if (doc_type == "Накладна") {
        file_name = file_name + "/buy_documents/" + date + ".pdf";
    } else if (doc_type == "Чек") {
        file_name = file_name + "/sale_documents/" + date + ".pdf";
    };
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file_name);
    QPrintDialog *dialog = new QPrintDialog(&printer,0);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }
    delete document;
}

void Sale_department::on_date_hist_actions_dateChanged(const QDate &date)
{
    proxy_actions = Dialog_actions::renew_actions(db,ui->tableView_actions,ui->date_hist_actions);
}

void Sale_department::on_action_search_textChanged(const QString &arg1)
{
    proxy_actions->setFilterFixedString(arg1);

}


void Sale_department::on_contr_name_search_textChanged(const QString &arg1)
{
    proxy_contr->setFilterKeyColumn(0);
    proxy_contr->setFilterFixedString(arg1);
}

void Sale_department::on_contr_address_search_textChanged(const QString &arg1)
{
    proxy_contr->setFilterKeyColumn(2);
    proxy_contr->setFilterFixedString(arg1);
}

void Sale_department::on_date_hist_programs_dateChanged(const QDate &date)
{
    proxy_programs = Dialog_programs::renew_programs(db, ui->tableView_programs, ui->date_hist_programs);
}

void Sale_department::on_program_search_textChanged(const QString &arg1)
{
    proxy_programs->setFilterFixedString(arg1);
}

void Sale_department::on_good_name_search_textChanged(const QString &arg1)
{
    proxy_goods->setFilterKeyColumn(0);
    proxy_goods->setFilterFixedString(arg1);
}

void Sale_department::on_good_price_search_textChanged(const QString &arg1)
{
    proxy_goods->setFilterKeyColumn(1);
    proxy_goods->setFilterFixedString(arg1);
}
