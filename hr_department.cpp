#include "hr_department.h"
#include "dialogentry.h"


HR_department::HR_department(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HR_department)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;

    showStaffTable();
}

HR_department::~HR_department()
{
    delete ui;
}

void HR_department::showStaffTable()
{
    QString viewDate = ui->date_historyView->date().toString("yyyy-MM-dd");
    QSqlQueryModel *model = db->getQueryModel(
        "select * from \"Myronenko_O\".show_staff where date_in <= '" + viewDate + "' and (date_out is null or date_out >= '" + viewDate + "');"
    );

    model->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(1, Qt::Horizontal, tr("Ім'я"));
    model->setHeaderData(2, Qt::Horizontal, tr("Прізвище"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_staff->setModel(proxyModel);
    ui->table_staff->setSortingEnabled(true);
    ui->table_staff->resizeColumnsToContents();
    ui->table_staff->setColumnHidden(3, true);
    ui->table_staff->setColumnHidden(4, true);
    ui->table_staff->setColumnHidden(5, true);
    ui->table_staff->setColumnHidden(6, true);
    ui->table_staff->setColumnHidden(7, true);
    ui->table_staff->setColumnHidden(8, true);
    ui->table_staff->setColumnHidden(9, true);

    for (int c = 0; c < ui->table_staff->horizontalHeader()->count(); ++c)
    {
        ui->table_staff->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void HR_department::on_button_closeWindow_clicked()
{
    this->close();
}

void HR_department::on_button_editPersInfo_clicked()
{
    Dialog_editPersInfo* dialog_editPersInfo = new Dialog_editPersInfo(db, selectedStaffId);
    dialog_editPersInfo->show();
}

//void MainWindow::on_tableView_actions_pressed(const QModelIndex &index)
//{
//    ui->add_action_button->setEnabled(false);
//    ui->update_action->setEnabled(true);
//    ui->delete_action->setEnabled(true);
//    int row = index.row();
//    QString name = index.sibling(row, 0).data().toString();
//    old_action_name = name;
//    qDebug() << old_action_name << endl;
//    QDate start = index.sibling(row, 2).data().toDate();
//    QString str_start = start.toString();
//    QDate stop = index.sibling(row, 3).data().toDate();
//    QString str_stop = stop.toString();
//    int percent = index.sibling(row, 1).data().toInt();
//    QString str_percent = QString::number(percent);
//    ui->action_name_field->setText(name);
//    ui->action_percent_field->setText(str_percent);
//    ui->start_action_date->setDate(start);
//    ui->stop_action_date->setDate(stop);
//}

void HR_department::on_table_staff_pressed(const QModelIndex &index)
{
    ui->button_showPersInfo->setEnabled(true);
    ui->button_editPersInfo->setEnabled(true);
    ui->button_changePersPosition->setEnabled(true);
    ui->button_addPersAbsence->setEnabled(true);
    ui->button_changePersSchedule->setEnabled(true);
    ui->button_firePers->setEnabled(true);

    int row = index.row();
    selectedStaffId = index.sibling(row, 4).data().toString();
}

void HR_department::on_date_historyView_dateChanged()
{
    showStaffTable();
}
