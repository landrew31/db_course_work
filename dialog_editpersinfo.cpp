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

    QSqlQueryModel *modelPerson = db->getQueryModel(
        "select * from \"Myronenko_O\".person where \"Id_person\" = " + persId + ";"
    );
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


    QString skillsQuery =
            "select skill_name, skill_description, per_skills.\"Id_person\", per_skills.\"Id_skill\" "
            "from \"Myronenko_O\".personal_skills per_skills "
                "join \"Myronenko_O\".skills "
                "on per_skills.\"Id_skill\" = skills.\"Id_skill\" "
            "where per_skills.\"Id_person\" = " + persId + ";";
    QSqlQueryModel *modelPersonSkills = db->getQueryModel(skillsQuery);
    int skillsCount = modelPersonSkills->rowCount();
    if (DEBUGMODE) qDebug() << "Dialog_editPersInfo got modelPersonSkills:";
    for (int i=0; i < skillsCount; i++)
    {
        index = modelPersonSkills->index(i, 0);
        if (DEBUGMODE) qDebug() << index.data(Qt::DisplayRole).toString();

        QString weditName = QString("lineEdit_skill%1").arg(i+1);
        QLineEdit* wedit = ui->frame_editFrame->findChild<QLineEdit*>(weditName);
        if (wedit)
        {
            if (DEBUGMODE) qDebug() << "!- " << weditName << " already exists";
            wedit->setText( index.data(Qt::DisplayRole).toString() );
            continue;
        }

        wedit  = new QLineEdit(index.data(Qt::DisplayRole).toString());
        if (DEBUGMODE) qDebug() << "!- " << weditName << " created";
        QString labelTitle = QString("Навичка %1").arg(i+1);
        QLabel* label  = new QLabel(labelTitle);
        wedit->setObjectName(weditName);

        ui->layout_persSkills->addWidget(label, i, 0);
        ui->layout_persSkills->addWidget(wedit, i, 1);
    }
    if (DEBUGMODE) qDebug() << endl;

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
    db->executeQuery(updateQuery, "admin", this);
}

