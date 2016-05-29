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
    showPositTable();
}

HR_department::~HR_department()
{
    delete ui;
}


//-----------
// STAFF TAB
//-----------


void HR_department::showStaffTable()
{
    QString viewDate = ui->date_historyView->date().toString("yyyy-MM-dd");
    QString queryText =
            "select * from \"Myronenko_O\".show_staff "
            "where date_in <= '" + viewDate + "' "
                "and (date_out is null or date_out >= '" + viewDate + "'"
            ");";
    QSqlQueryModel *model = db->getQueryModel(queryText);

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
    Dialog_editPersInfo* dialog_editPersInfo = new Dialog_editPersInfo(db, selectedStaffId, this);
    dialog_editPersInfo->show();
    connect(dialog_editPersInfo, SIGNAL(accepted()), this, SLOT(showStaffTable()));
}

void HR_department::on_table_staff_pressed(const QModelIndex &index)
{
//    ui->button_showPersInfo->setEnabled(true);
    ui->button_editPersInfo->setEnabled(true);
//    ui->button_changePersPosition->setEnabled(true);
//    ui->button_addPersAbsence->setEnabled(true);
//    ui->button_changePersSchedule->setEnabled(true);
//    ui->button_firePers->setEnabled(true);

    int row = index.row();
    selectedStaffId = index.sibling(row, 4).data().toInt();
}

void HR_department::on_date_historyView_dateChanged()
{
    showStaffTable();
}



//---------------
// POSITIONS TAB
//---------------

void HR_department::showPositTable()
{
    QString queryText =
            "select * from \"Myronenko_O\".show_positions;";
    QSqlQueryModel *model = db->getQueryModel(queryText);

    model->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(1, Qt::Horizontal, tr("Кількість робітників"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_positions->setModel(proxyModel);
    ui->table_positions->setSortingEnabled(true);
    ui->table_positions->resizeColumnsToContents();
    ui->table_positions->setColumnHidden(1, true);
    for (int c = 0; c < ui->table_positions->horizontalHeader()->count(); ++c)
    {
        ui->table_positions->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void HR_department::on_table_positions_pressed(const QModelIndex &index)
{
    int row = index.row();
    //    ui->button_showPositInfo->setEnabled(true);
    ui->button_editPosition->setEnabled(true);
    int selectedPositStaffCount = index.sibling(row, 1).data().toInt();
    if (selectedPositStaffCount == 0) ui->button_deletePosition->setEnabled(true);

    selectedPositId = index.sibling(row, 1).data().toInt();
}

void HR_department::on_button_editPosition_clicked()
{
    Dialog_editPosition* dialog_editPosition = new Dialog_editPosition(db, selectedPositId, this);
    dialog_editPosition->show();
    connect(dialog_editPosition, SIGNAL(accepted()), this, SLOT(showPositTable()));
}
