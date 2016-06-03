#include "dialog_showstaffprofile.h"
#include "ui_dialog_showstaffprofile.h"

Dialog_showStaffProfile::Dialog_showStaffProfile(DB_setup* db, int selectedPersId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_showStaffProfile)
{
    ui->setupUi(this);
    this->db = db;
    persId = selectedPersId;
    showInpValues();
}

Dialog_showStaffProfile::~Dialog_showStaffProfile()
{
    delete ui;
}

void Dialog_showStaffProfile::showInpValues()
{
    QString queryText;
    QModelIndex index;

    //-------------
    // PERSINFO BLOCK
    //-------------

    queryText = QString("select * from \"Myronenko_O\".person where \"Id_person\" = %1;").arg(persId);
    QSqlQueryModel *modelPerson = db->getQueryModel(queryText);
    if (DEBUGMODE)
    {
        qDebug() << "Dialog_editPersInfo got modelPerson:";
        for (int i=0; i < modelPerson->columnCount(); i++)
        {
            index = modelPerson->index(0, i);
            qDebug() << index.data(Qt::DisplayRole).toString();
        }
    }
    if (DEBUGMODE) qDebug() << endl;

    index = modelPerson->index(0, 1);
    QString name = index.data(Qt::DisplayRole).toString();
    index = modelPerson->index(0, 2);
    QString surname = index.data(Qt::DisplayRole).toString();
    ui->staffNameSurname->setText(name + " " + surname);

    index = modelPerson->index(0, 3);
    QDate birthday = index.data(Qt::DisplayRole).toDate();
    ui->staffAge->setText(birthday.toString("yyyy-MM-dd"));

    index = modelPerson->index(0, 4);
    QString education = index.data(Qt::DisplayRole).toString();
    ui->staffEdu->setText(education);



    //-------------
    // LIST SKILLS BLOCK
    //-------------

    queryText = QString(
            "select skill_name, skill_description "
            "from \"Myronenko_O\".personal_skills per_skills "
                "join \"Myronenko_O\".skills "
                "on per_skills.\"Id_skill\" = skills.\"Id_skill\" "
            "where per_skills.\"Id_person\" = %1 "
            "order by skill_name;").arg(persId);
    QSqlQueryModel* modelPersonSkills = db->getQueryModel(queryText);
    modelPersonSkills->setHeaderData(0, Qt::Horizontal, tr("Навичка"));
    modelPersonSkills->setHeaderData(1, Qt::Horizontal, tr("Описання"));
    ui->skillsTable->setModel(modelPersonSkills);
    ui->skillsTable->resizeColumnsToContents();
    ui->skillsTable->resizeRowsToContents();
    ui->skillsTable->verticalHeader()->setDefaultSectionSize(50);
    for (int c = 0; c < ui->skillsTable->horizontalHeader()->count(); ++c)
    {
        ui->skillsTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }


    //-------------
    // WORK HISTORY BLOCK
    //-------------

    queryText = QString(
            "select linkposition.posit_name, staff.date_in, staff.date_out "
                "from \"Myronenko_O\".staff staff "
                    "join "
                    "(\"Myronenko_O\".vacancies vacancies "
                        "join \"Myronenko_O\".positions positions "
                        "on vacancies.\"Id_position\" = positions.\"Id_position\") "
                    "as linkposition "
                    "on staff.\"Id_vacancy\" = linkposition.\"Id_vacancy\" "
                "where \"Id_person\" = %1 "
                "order by staff.date_in desc;").arg(persId);
    QSqlQueryModel* modelWorkHistory = db->getQueryModel(queryText);
    modelWorkHistory->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    modelWorkHistory->setHeaderData(1, Qt::Horizontal, tr("Початок"));
    modelWorkHistory->setHeaderData(2, Qt::Horizontal, tr("Кінець"));
    ui->workHistoryTable->setModel(modelWorkHistory);
    ui->workHistoryTable->resizeColumnsToContents();
    for (int c = 0; c < ui->workHistoryTable->horizontalHeader()->count(); ++c)
    {
        ui->workHistoryTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}
