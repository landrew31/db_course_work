#include "dialog_editposition.h"
#include "ui_dialog_editposition.h"

Dialog_editPosition::Dialog_editPosition(DB_setup* db, int selectedPositId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_editPosition)
{
    ui->setupUi(this);
    this->db = db;
    positId = selectedPositId;
    showInpValues();
}

Dialog_editPosition::~Dialog_editPosition()
{
    delete ui;
}

void Dialog_editPosition::showInpValues()
{
    QString queryText;
    QModelIndex index;


    //-------------
    // EDIT SKILLS BLOCK
    //-------------

    queryText =
            "select \"Id_skill\", skill_name "
            "from \"Myronenko_O\".skills;";
    modelAllSkills = db->getQueryModel(queryText);
    int allSkillsCount = modelAllSkills->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_editPosition got modelAllSkills:";
    ui->comboBox_selectSkill->clear();
    for (int i=0; i < allSkillsCount; i++)
    {
        index = modelAllSkills->index(i, 1);
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();
        ui->comboBox_selectSkill->addItem(index.data(Qt::DisplayRole).toString());
    }
    if (DEBUGMODE) qDebug() << endl;

    if (positId == -1) return;


    //-------------
    // POSITINFO BLOCK
    //-------------

    queryText = QString(
        "select * from \"Myronenko_O\".positions where \"Id_position\" = %1;").arg(positId);
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
    ui->positDescr->setText(descr);


    //-------------
    // LIST SKILLS BLOCK
    //-------------

    queryText = QString(
                "select skill_name, skill_description, nec_skills.\"Id_position\", nec_skills.\"Id_skill\" "
                "from \"Myronenko_O\".neccessary_skills nec_skills "
                    "join \"Myronenko_O\".skills skills "
                    "on nec_skills.\"Id_skill\" = skills.\"Id_skill\" "
                "where nec_skills.\"Id_position\" = %1;").arg(positId);
    QSqlQueryModel *modelPositionSkills = db->getQueryModel(queryText);
    int skillsCount = modelPositionSkills->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_editPosition got modelPositionSkills:";   

    for (int i=0; i < skillsCount; i++)
    {
        index = modelPositionSkills->index(i, 0);
        QString skillName = index.data(Qt::DisplayRole).toString();
        index = modelPositionSkills->index(i, 3);
        int skillId = index.data(Qt::DisplayRole).toInt();

        if (DEBUGMODE) qDebug() << "-" << skillName;
        inserSkillIntoList(skillName, skillId);
    }
    if (DEBUGMODE) qDebug() << endl;
}

void Dialog_editPosition::on_button_addSkill_clicked()
{
    QString newSkillName = ui->comboBox_selectSkill->currentText();
    int newSkillId = searchIdByNameInModel(newSkillName, modelAllSkills, 0, 1);
    if (DEBUGMODE) qDebug() << "New skill added for" << positId << "position:" << newSkillName << newSkillId << endl;
    inserSkillIntoList(newSkillName, newSkillId);
}

void Dialog_editPosition::on_button_createSkill_clicked()
{
    Dialog_createSkill* createSkillWindow = new Dialog_createSkill(db, this);
    createSkillWindow->show();
    connect(createSkillWindow, SIGNAL(accepted()), this, SLOT(showInpValues()));
}

void Dialog_editPosition::accept()
{
    ui->buttonBox->setDisabled(true);
    if (DEBUGMODE) qDebug() << "editPosition dialog accepted:";
    QString name = ui->positName->text();
    QString description = ui->positDescr->toPlainText();
    if (DEBUGMODE) qDebug() << "data to insert/update:" << name << description;
    QString queryText = "";


    // INFO INSERT / UPDATE
    if (positId == -1)
    {
        queryText = QString(
            "insert into \"Myronenko_O\".positions (posit_name, posit_description)"
            "values('%1', '%2');").arg(name).arg(description);
        db->executeQuery(queryText, "admin", this, 1);
        queryText = QString(
                    "select \"Id_position\" "
                    "from \"Myronenko_O\".positions "
                    "where posit_name = '%1';").arg(name);
        QSqlQueryModel *modelNewPosition = db->getQueryModel(queryText);
        QModelIndex index = modelNewPosition->index(0, 0);
        positId = index.data(Qt::DisplayRole).toInt();
    } else {
        queryText = QString(
            "delete from \"Myronenko_O\".neccessary_skills "
            "where \"Id_position\" = %1;").arg(positId);
        db->executeQuery(queryText, "admin", this, -1);

        queryText = QString(
            "update \"Myronenko_O\".positions set "
                "posit_name = '%1', "
                "posit_description = '%2' "
            "where \"Id_position\" = %3;").arg(name).arg(description).arg(positId);
        db->executeQuery(queryText, "admin", this, 2);
    }


    // SKILLS INSERT / UPDATE
    for (int i=0; i < skills.length(); i++)
    {
        queryText = QString(
            "insert into \"Myronenko_O\".neccessary_skills (\"Id_skill\", \"Id_position\") "
                "values (%1, %2);").arg(skills[i]).arg(positId);
        db->executeQuery(queryText, "admin", this, -1);
    };

    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}

void Dialog_editPosition::removeSkill(){
    int skillId = 0;
    if (DEBUGMODE) qDebug() << "Remove" << skillId << "skill" << endl;
}

void Dialog_editPosition::inserSkillIntoList(QString skillName, int skillId)
{
    QLabel* skillVal  = new QLabel(skillName);

    QPushButton* delButton  = new QPushButton(QString("Видалити"));
    delButton->setCursor(Qt::PointingHandCursor);

    int rowNumber = ui->layout_positSkills->rowCount();
    ui->layout_positSkills->addWidget(skillVal, rowNumber, 0);
    ui->layout_positSkills->addWidget(delButton, rowNumber, 1);

    skills.append(skillId);
    connect(delButton, SIGNAL(clicked()), this, SLOT( removeSkill() ));
}
