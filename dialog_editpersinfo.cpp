#include "dialog_editpersinfo.h"


Dialog_editPersInfo::Dialog_editPersInfo(DB_setup *db, int selectedPersId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUi_editPersInfo)
{
    ui->setupUi(this);
    this->db = db;

    persId = selectedPersId;
    showInpValues();
}

Dialog_editPersInfo::~Dialog_editPersInfo()
{
    delete ui;
}

void Dialog_editPersInfo::showInpValues()
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
    if (DEBUGMODE) qDebug() << "Dialog_editPersInfo got modelAllSkills:";
    ui->comboBox_selectSkill->clear();
    for (int i=0; i < allSkillsCount; i++)
    {
        index = modelAllSkills->index(i, 1);
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();
        ui->comboBox_selectSkill->addItem(index.data(Qt::DisplayRole).toString());
    }
    if (DEBUGMODE) qDebug() << endl;

    if (persId == -1) return;


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

    queryText = QString(
            "select skill_name, skill_description, per_skills.\"Id_person\", per_skills.\"Id_skill\" "
            "from \"Myronenko_O\".personal_skills per_skills "
                "join \"Myronenko_O\".skills "
                "on per_skills.\"Id_skill\" = skills.\"Id_skill\" "
            "where per_skills.\"Id_person\" = %1;").arg(persId);
    QSqlQueryModel *modelPersonSkills = db->getQueryModel(queryText);
    int skillsCount = modelPersonSkills->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_editPersInfo got modelPersonSkills:";

    for (int i=0; i < skillsCount; i++)
    {
        index = modelPersonSkills->index(i, 0);
        QString skillName = index.data(Qt::DisplayRole).toString();
        index = modelPersonSkills->index(i, 3);
        int skillId = index.data(Qt::DisplayRole).toInt();
        if (DEBUGMODE) qDebug() << "-" << skillName;
        inserSkillIntoList(skillName, skillId);
    }
    if (DEBUGMODE) qDebug() << endl;
}

void Dialog_editPersInfo::on_button_addSkill_clicked()
{
    QString newSkillName = ui->comboBox_selectSkill->currentText();
    int newSkillId = searchIdByNameInModel(newSkillName, modelAllSkills, 0, 1);
    if (DEBUGMODE) qDebug() << "Selected new skill for" << persId << "person:" << newSkillName << newSkillId << endl;
    inserSkillIntoList(newSkillName, newSkillId);
}

void Dialog_editPersInfo::accept()
{
    ui->buttonBox->setDisabled(true);
    if (DEBUGMODE) qDebug() << "editPersInfo dialog accepted:";
    QString name = ui->persName->text();
    QString surname = ui->persSurname->text();
    QString birthday = ui->persBirthDate->date().toString("yyyy-MM-dd");
    QString education = ui->persEdu->text();
    if (DEBUGMODE) qDebug() << "data to update:" << name << surname << birthday << education;
    QString queryText = "";


    // INFO UPDATE
    if (persId == -1)
    {
        queryText = QString(
            "inser into \"Myronenko_O\".person values("
                "per_name = '%1', "
                "per_surname = '%2', "
                "birthday = '%3', "
                "education = '%4');").arg(name).arg(surname).arg(birthday).arg(education);
        db->executeQuery(queryText, "admin", this, 1);
        queryText = QString(
                    "select \"Id_person\" "
                    "from \"Myronenko_O\".person "
                    "where per_name = '%1' "
                      "and per_surname = %2;").arg(name).arg(surname);
        QSqlQueryModel *modelNewPosition = db->getQueryModel(queryText);
        QModelIndex index = modelNewPosition->index(0, 0);
        persId = index.data(Qt::DisplayRole).toInt();
    } else {
        queryText = QString(
            "delete from \"Myronenko_O\".personal_skills "
            "where \"Id_person\" = %1;").arg(persId);
        db->executeQuery(queryText, "admin", this, -1);

        queryText = QString(
            "update \"Myronenko_O\".person set "
                "per_name = '%1', "
                "per_surname = '%2', "
                "birthday = '%3', "
                "education = '%4' "
             "where \"Id_person\" = %5;").arg(name).arg(surname).arg(birthday).arg(education).arg(persId);
        db->executeQuery(queryText, "admin", this, 2);
    }


    // SKILLS UPDATE
    for (int i=0; i < skills.length(); i++)
    {
        queryText = QString(
            "insert into \"Myronenko_O\".personal_skills (\"Id_person\", \"Id_skill\") "
                "values (%1, %2);").arg(persId).arg(skills[i]);
        qDebug() << queryText;
        db->executeQuery(queryText, "admin", this, -1);
    };


    this->accepted();
    this->close();
    ui->buttonBox->setEnabled(true);
}

void Dialog_editPersInfo::on_button_createSkill_clicked()
{
    Dialog_createSkill* createSkillWindow = new Dialog_createSkill(db, this);
    createSkillWindow->show();
    connect(createSkillWindow, SIGNAL(accepted()), this, SLOT(showInpValues()));
}

void Dialog_editPersInfo::removeSkill(){
    int skillId = 0;
    if (DEBUGMODE) qDebug() << "Remove" << skillId << "skill" << endl;
}

void Dialog_editPersInfo::inserSkillIntoList(QString skillName, int skillId)
{
    QLabel* skillVal  = new QLabel(skillName);

    QPushButton* delButton  = new QPushButton(QString("Видалити"));
    delButton->setCursor(Qt::PointingHandCursor);

    int rowNumber = ui->layout_persSkills->rowCount();
    ui->layout_persSkills->addWidget(skillVal, rowNumber, 0);
    ui->layout_persSkills->addWidget(delButton, rowNumber, 1);

    skills.append(skillId);
    connect(delButton, SIGNAL(clicked()), this, SLOT( removeSkill() ));
}
