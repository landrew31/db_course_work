#include "dialog_editposition.h"
#include "ui_dialog_editposition.h"

Dialog_editPosition::Dialog_editPosition(DB_setup* db, int selectedPositId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_editPosition)
{
    ui->setupUi(this);
    this->db = db;
    positId = selectedPositId;
    qDebug() << "positId:" << positId <<endl;

    showInpValues();
}

Dialog_editPosition::~Dialog_editPosition()
{
    delete ui;
}

void Dialog_editPosition::showInpValues()
{
    QModelIndex index;

    //-------------
    // POSITINFO BLOCK
    //-------------

    QString queryText = QString(
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
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();

        QString skillValName = QString("label_skill%1").arg(i+1);
        QLabel* skillVal = ui->frame_editFrame->findChild<QLabel*>(skillValName);
        if (skillVal)
        {
            if (DEBUGMODE) qDebug() << "!- " << skillValName << " already exists";
            skillVal->setText( index.data(Qt::DisplayRole).toString() );
            continue;
        }

        skillVal  = new QLabel(index.data(Qt::DisplayRole).toString());
        skillVal->setObjectName(skillValName);
        if (DEBUGMODE) qDebug() << "!- " << skillValName << " created";
        QString labelTitle = QString("Навичка %1").arg(i+1);
        QLabel* label  = new QLabel(labelTitle);
        QPushButton* delButton  = new QPushButton(QString("Видалити"));
        delButton->setCursor(Qt::PointingHandCursor);
        index = modelPositionSkills->index(i, 3);
//        int skillId = index.data(Qt::DisplayRole).toInt();
        connect(delButton, SIGNAL(clicked()), this, SLOT( removeSkill() ));

        ui->layout_positSkills->addWidget(label, i, 0);
        ui->layout_positSkills->addWidget(skillVal, i, 1);
        ui->layout_positSkills->addWidget(delButton, i, 2);
    }
    if (DEBUGMODE) qDebug() << endl;

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
}


void Dialog_editPosition::on_button_addSkill_clicked()
{
    QString newSkillName = ui->comboBox_selectSkill->currentText();
    int newSkillId = searchIdByNameInModel(newSkillName, modelAllSkills, 0, 1);
    if (DEBUGMODE) qDebug() << "Selected new skill for" << positId << "position:" << newSkillName << newSkillId << endl;
    QString queryText = QString(
        "insert into \"Myronenko_O\".neccessary_skills (\"Id_skill\", \"Id_position\") "
            "values (%1, %2);").arg(newSkillId).arg(positId);
    db->executeQuery(queryText, "admin", this, 1);
    showInpValues();
}

void Dialog_editPosition::on_button_createSkill_clicked()
{
    Dialog_createSkill* createSkillWindow = new Dialog_createSkill(db, this);
    createSkillWindow->show();
    connect(createSkillWindow, SIGNAL(accepted()), this, SLOT(showInpValues()));
}

void Dialog_editPosition::accept()
{
    if (DEBUGMODE) qDebug() << "dialog accepted";
    QString name = ui->positName->text();
    QString description = ui->positDescr->toPlainText();
    if (DEBUGMODE) qDebug() << "data to update:" << name << description;
    QString queryText = QString("update \"Myronenko_O\".positions set "
        "posit_name = '%1', "
        "posit_description = '%2' "
      "where \"Id_position\" = %3;").arg(name).arg(description).arg(positId);
    db->executeQuery(queryText, "admin", this, 2);
    this->accepted();
    this->close();
}

void Dialog_editPosition::removeSkill(){
    int skillId = 0;
    if (DEBUGMODE) qDebug() << "Remove" << skillId << "skill" << endl;
}
