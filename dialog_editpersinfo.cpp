#include "dialog_editpersinfo.h"


Dialog_editPersInfo::Dialog_editPersInfo(DB_setup *db, QString selectedPersId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUi_editPersInfo)
{
    ui->setupUi(this);
    this->db = db;

    persId = selectedPersId;
    if (DEBUGMODE) qDebug() << "selectedPersId: " << persId;
    showInpValues();
}

Dialog_editPersInfo::~Dialog_editPersInfo()
{
    delete ui;
}

void Dialog_editPersInfo::showInpValues()
{
    QModelIndex index;

    //-------------
    // PERSINFO BLOCK
    //-------------

    QString queryText = "select * from \"Myronenko_O\".person where \"Id_person\" = " + persId + ";";
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
    ui->persName->setText(name);

    index = modelPerson->index(0, 2);
    QString surname = index.data(Qt::DisplayRole).toString();
    ui->persSurname->setText(surname);

    index = modelPerson->index(0, 3);
    QDate birthday =index.data(Qt::DisplayRole).toDate();
    ui->persBirthDate->setDate(birthday);

    index = modelPerson->index(0, 4);
    QString education = index.data(Qt::DisplayRole).toString();
    ui->persEdu->setText(education);

    //-------------
    // LIST SKILLS BLOCK
    //-------------

    queryText =
            "select skill_name, skill_description, per_skills.\"Id_person\", per_skills.\"Id_skill\" "
            "from \"Myronenko_O\".personal_skills per_skills "
                "join \"Myronenko_O\".skills "
                "on per_skills.\"Id_skill\" = skills.\"Id_skill\" "
            "where per_skills.\"Id_person\" = " + persId + ";";
    QSqlQueryModel *modelPersonSkills = db->getQueryModel(queryText);
    int skillsCount = modelPersonSkills->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_editPersInfo got modelPersonSkills:";
    for (int i=0; i < skillsCount; i++)
    {
        index = modelPersonSkills->index(i, 0);
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

        ui->layout_persSkills->addWidget(label, i, 0);
        ui->layout_persSkills->addWidget(skillVal, i, 1);
        ui->layout_persSkills->addWidget(delButton, i, 2);
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
    if (DEBUGMODE) qDebug() << "Dialog_editPersInfo got modelAllSkills:";
    for (int i=0; i < allSkillsCount; i++)
    {
        index = modelAllSkills->index(i, 1);
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();
        ui->comboBox_selectSkill->addItem(index.data(Qt::DisplayRole).toString());
    }
    if (DEBUGMODE) qDebug() << endl;
}

void Dialog_editPersInfo::on_button_addSkill_clicked()
{
    QString newSkillName = ui->comboBox_selectSkill->currentText();
    QString newSkillId = searchSkillIdByNameInModel(newSkillName);
    if (DEBUGMODE) qDebug() << "Selected new skill: " << newSkillName << newSkillId;
}

void Dialog_editPersInfo::accept()
{
    if (DEBUGMODE) qDebug() << "dialog accepted";
    QString name = ui->persName->text();
    QString surname = ui->persSurname->text();
    QString birthday = ui->persBirthDate->date().toString("yyyy-MM-dd");
    QString education = ui->persEdu->text();
    if (DEBUGMODE) qDebug() << "data to update: " << name << surname << birthday << education;
    QString updateQuery = "update \"Myronenko_O\".person "
        "set per_name = '" + name + "', "
        "per_surname = '" + surname + "', "
        "birthday = '" + birthday + "', "
        "education = '" + education + "' "
      "where \"Id_person\" = " + persId + ";";
    db->executeQuery(updateQuery, "admin", this, 2);
}

QString Dialog_editPersInfo::searchSkillIdByNameInModel(QString skillName)
{
    QString id = "266";
    return id;
}
