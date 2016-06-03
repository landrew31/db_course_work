#include "dialog_staffabsence.h"
#include "ui_dialog_staffabsence.h"

Dialog_staffabsence::Dialog_staffabsence(DB_setup* db, int selectedStaffId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_staffabsence)
{
    ui->setupUi(this);
    this->db = db;
    staffId = selectedStaffId;
    showInpValues();
}

Dialog_staffabsence::~Dialog_staffabsence()
{
    delete ui;
}

void Dialog_staffabsence::showInpValues()
{
    QString queryText;
    QModelIndex index;

    queryText = QString(
            "select per_name, per_surname from \"Myronenko_O\".show_staff "
                "where \"Id_staff\" = %1;").arg(staffId);
    QSqlQueryModel* model = db->getQueryModel(queryText);

    index = model->index(0, 0);
    QString name = index.data(Qt::DisplayRole).toString();
    index = model->index(0, 1);
    QString surname = index.data(Qt::DisplayRole).toString();
    ui->staffNameSurname->setText(name + " " + surname);

    queryText = QString(
            "select abs_name, date_in, date_out, abs_descr "
                "from \"Myronenko_O\".absences absences "
                    "join \"Myronenko_O\".absence_type absence_type "
                        "on absences.\"Id_abs_type\" = absence_type.\"Id_abs_type\" "
                "where \"Id_stuff\" = %1;").arg(staffId);
    qDebug() << queryText << endl;
    model = db->getQueryModel(queryText);
    model->setHeaderData(0, Qt::Horizontal, tr("Тип"));
    model->setHeaderData(1, Qt::Horizontal, tr("Початок"));
    model->setHeaderData(2, Qt::Horizontal, tr("Кінець"));
    model->setHeaderData(3, Qt::Horizontal, tr("Опис"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->absenceTable->setModel(proxyModel);
    ui->absenceTable->setSortingEnabled(true);
    ui->absenceTable->resizeColumnsToContents();
    for (int c = 0; c < ui->absenceTable->horizontalHeader()->count(); ++c)
    {
        ui->absenceTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

}

void Dialog_staffabsence::on_addAbsence_clicked()
{
    Dialog_addStaffAbsence* dialog_addStaffAbsence = new Dialog_addStaffAbsence(db, staffId, this);
    dialog_addStaffAbsence->show();
    connect(dialog_addStaffAbsence, SIGNAL(accepted()), this, SLOT(showInpValues()));
}
