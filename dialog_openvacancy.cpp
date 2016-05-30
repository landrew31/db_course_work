#include "dialog_openvacancy.h"
#include "ui_dialog_openvacancy.h"

Dialog_openVacancy::Dialog_openVacancy(DB_setup* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_openVacancy)
{
    ui->setupUi(this);
    this->db = db;

    showInpValues();
}

Dialog_openVacancy::~Dialog_openVacancy()
{
    delete ui;
}

void Dialog_openVacancy::showInpValues()
{
    QString queryText;
    QModelIndex index;

    //-------------
    // POSITIONS BLOCK
    //-------------

    queryText =
            "select \"Id_position\", posit_name "
            "from \"Myronenko_O\".positions "
            "where exists = true;";
    modelAllPositions = db->getQueryModel(queryText);
    int allPositCount = modelAllPositions->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_openVacancy got modelAllPositions:" << allPositCount;
    ui->select_positions->clear();
    for (int i=0; i < allPositCount; i++)
    {
        index = modelAllPositions->index(i, 1);
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();
        ui->select_positions->addItem(index.data(Qt::DisplayRole).toString());
    }
    if (DEBUGMODE) qDebug() << endl;

    //-------------
    // INFO BLOCK
    //-------------

    ui->openDate->setDate(QDate::currentDate());
}

void Dialog_openVacancy::accept()
{
    ui->buttonBox->setDisabled(true);
    int vacCount = ui->vacCount->value();
    QString positName = ui->select_positions->currentText();
    int positId = searchIdByNameInModel(positName, modelAllPositions, 0, 1);
    QString openDate = ui->openDate->date().toString("yyyy-MM-dd");
    QString queryText = "";
    for (int i=0; i < vacCount; i++)
    {
        queryText =  QString(
            "insert into \"Myronenko_O\".vacancies (type, date, \"Id_position\") "
                "values (1, '%1', %2);").arg(openDate).arg(positId);
        db->executeQuery(queryText, "admin", this, i == vacCount-1 ? 1 : -1);
    }
    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}

void Dialog_openVacancy::on_button_createPosition_clicked()
{
    Dialog_editPosition* dialog_addPosition = new Dialog_editPosition(db, -1, this);
    dialog_addPosition->show();
    connect(dialog_addPosition, SIGNAL(accepted()), this, SLOT(showInpValues()));
}
