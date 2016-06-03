#include "dialog_showpositinfo.h"
#include "ui_dialog_showpositinfo.h"

Dialog_showPositInfo::Dialog_showPositInfo(DB_setup* db, int selectedPositId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_showPositInfo)
{
    ui->setupUi(this);
    this->db = db;
    positId = selectedPositId;
    showInpValues();
}

Dialog_showPositInfo::~Dialog_showPositInfo()
{
    delete ui;
}

void Dialog_showPositInfo::showInpValues()
{
    QString queryText;
    QModelIndex index;




    //-------------
    // POSITINFO BLOCK
    //-------------

    queryText = QString(
        "select \"Id_position\", posit_name, posit_description "
        "from \"Myronenko_O\".positions where \"Id_position\" = %1;").arg(positId);
    QSqlQueryModel *modelPosition = db->getQueryModel(queryText);
    if (DEBUGMODE)
    {
        qDebug() << "Dialog_editPosition got modelPosition:";
        for (int i=0; i < modelPosition->columnCount(); i++)
        {
            index = modelPosition->index(0, i);
            qDebug() << index.data(Qt::DisplayRole).toString();
        }
    }
    if (DEBUGMODE) qDebug() << endl;

    index = modelPosition->index(0, 1);
    QString name = index.data(Qt::DisplayRole).toString();
    ui->positName->setText(name);

    index = modelPosition->index(0, 2);
    QString descr = index.data(Qt::DisplayRole).toString();
    ui->positDescription->setText(descr);




    //-------------
    // LIST SKILLS BLOCK
    //-------------

    queryText = QString(
        "select skill_name, skill_description "
            "from \"Myronenko_O\".neccessary_skills nec_skills "
                "join \"Myronenko_O\".skills skills "
                    "on nec_skills.\"Id_skill\" = skills.\"Id_skill\" "
            "where nec_skills.\"Id_position\" = %1 "
            "order by skill_name;").arg(positId);
    QSqlQueryModel *model = db->getQueryModel(queryText);
    model->setHeaderData(0, Qt::Horizontal, tr("Навичка"));
    model->setHeaderData(1, Qt::Horizontal, tr("Описання"));
    ui->table_positSkills->setModel(model);
    ui->table_positSkills->resizeColumnsToContents();
    ui->table_positSkills->resizeRowsToContents();
    ui->table_positSkills->verticalHeader()->setDefaultSectionSize(50);
    for (int c = 0; c < ui->table_positSkills->horizontalHeader()->count(); ++c)
    {
        ui->table_positSkills->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}
