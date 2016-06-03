#include "dialog_addstaffabsence.h"
#include "ui_dialog_addstaffabsence.h"

Dialog_addStaffAbsence::Dialog_addStaffAbsence(DB_setup* db, int selectedStaffId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_addStaffAbsence)
{
    ui->setupUi(this);
    this->db = db;
    staffId = selectedStaffId;
    showInpValues();
    ui->absStart->setDate(QDate::currentDate());
    ui->absEnd->setDate(QDate::currentDate());
}

Dialog_addStaffAbsence::~Dialog_addStaffAbsence()
{
    delete ui;
}

void Dialog_addStaffAbsence::showInpValues()
{
    QString queryText;
    QModelIndex index;

    queryText =
        "select \"Id_abs_type\", abs_name "
            "from \"Myronenko_O\".absence_type "
            "order by abs_name;";
    allAbsTypes = db->getQueryModel(queryText);
    int allAbsTypesCount = allAbsTypes->rowCount();
    ui->selectAbsType->clear();
    for (int i=0; i < allAbsTypesCount; i++)
    {
        index = allAbsTypes->index(i, 1);
        ui->selectAbsType->addItem(index.data(Qt::DisplayRole).toString());
    }
}

void Dialog_addStaffAbsence::on_createAbsType_clicked()
{
    Dialog_createAbsType* dialog_createAbsType = new Dialog_createAbsType(db, this);
    dialog_createAbsType->show();
    connect(dialog_createAbsType, SIGNAL(accepted()), this, SLOT(showInpValues()));
}

void Dialog_addStaffAbsence::accept()
{
    ui->buttonBox->setDisabled(true);

    int absType = searchIdByNameInModel(
        ui->selectAbsType->currentText(),
        allAbsTypes,
        0,
        1
    );
    QString dateStart = ui->absStart->date().toString("yyyy-MM-dd");
    QString dateEnd  =  ui->absEnd->date().toString("yyyy-MM-dd");
    QString absDescr = ui->absDescription->toPlainText();

    if (DEBUGMODE) qDebug() << "new absence: staffId" << staffId << ", absType" << absType
        << ", start" << dateStart << ", end" << dateEnd << endl;
    QString queryText = QString(
        "select \"Myronenko_O\".add_absence(%1, '%2', '%3', %4, '%5');")
            .arg(staffId).arg(dateStart).arg(dateEnd).arg(absType).arg(absDescr);
    db->executeQuery(queryText, "admin", this, 1);

    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}
