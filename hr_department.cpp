#include "hr_department.h"
#include "dialogentry.h"


HR_department::HR_department(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HR_department)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;

    ui->date_historyView->setDate(QDate::currentDate());
    showAllTables();
}

HR_department::~HR_department()
{
    delete ui;
}

void HR_department::showAllTables()
{
    showPositTable();
    showStaffTable();
    showVacTable();
    if (db->getUser() == "admin")
    {
        ui->button_addPosition->setEnabled(true);
    }
}

void HR_department::return_to_dialogentry()
{
    DialogEntry* entryWindow = new DialogEntry(db);
    this->close();
    entryWindow->show();
}



//-----------
// STAFF TAB
//-----------

void HR_department::showStaffTable()
{
    QString viewDate = ui->date_historyView->date().toString("yyyy-MM-dd");
    QString queryText = QString(
            "select * from \"Myronenko_O\".show_staff "
            "where date_in <= '%1' "
                "and (date_out is null or date_out > '%2');").arg(viewDate).arg(viewDate);
    QSqlQueryModel* model = db->getQueryModel(queryText);

    model->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(1, Qt::Horizontal, tr("Ім'я"));
    model->setHeaderData(2, Qt::Horizontal, tr("Прізвище"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_staff->setModel(proxyModel);
    ui->table_staff->setSortingEnabled(true);
    ui->table_staff->resizeColumnsToContents();
    ui->table_staff->setColumnHidden(3, true);
    ui->table_staff->setColumnHidden(4, true);
    ui->table_staff->setColumnHidden(5, true);
    ui->table_staff->setColumnHidden(6, true);
    ui->table_staff->setColumnHidden(7, true);
    ui->table_staff->setColumnHidden(8, true);
    ui->table_staff->setColumnHidden(9, true);
    for (int c = 0; c < ui->table_staff->horizontalHeader()->count(); ++c)
    {
        ui->table_staff->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}


void HR_department::on_table_staff_pressed(const QModelIndex &index)
{
    ui->button_showPersInfo->setEnabled(true);
    ui->button_editPersInfo->setEnabled(true);
    ui->button_changePersPosition->setEnabled(true);
    ui->button_addPersAbsence->setEnabled(true);
//    ui->button_changePersSchedule->setEnabled(true);
    ui->button_firePers->setEnabled(true);
    ui->button_printReport->setEnabled(true);

    int row = index.row();
    selectedStaffId = index.sibling(row, 3).data().toInt();
    selectedPersId = index.sibling(row, 4).data().toInt();
}

void HR_department::on_button_showPersInfo_clicked()
{
    Dialog_showStaffProfile* dialog_showStaffProfile = new Dialog_showStaffProfile(db, selectedPersId, this);
    dialog_showStaffProfile->show();
    connect(dialog_showStaffProfile, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_editPersInfo_clicked()
{
    Dialog_editPersInfo* dialog_editPersInfo = new Dialog_editPersInfo(db, selectedPersId, this);
    dialog_editPersInfo->show();
    connect(dialog_editPersInfo, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_changePersPosition_clicked()
{
    Dialog_changePosition* dialog_changePosition = new Dialog_changePosition(db, selectedStaffId, selectedPersId, this);
    dialog_changePosition->show();
    connect(dialog_changePosition, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_addStuff_clicked()
{
    Dialog_addStaff* dialog_addStaff = new Dialog_addStaff(db, this);
    dialog_addStaff->show();
    connect(dialog_addStaff, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_date_historyView_dateChanged()
{
    showStaffTable();
}

void HR_department::on_updateStaffTable_clicked()
{
    showStaffTable();
}

void HR_department::on_button_closeWindow_clicked()
{
    return_to_dialogentry();
}

void HR_department::on_button_firePers_clicked()
{
    Dialog_fireStaff* dialog_fireStaff = new Dialog_fireStaff(db, selectedStaffId, selectedPersId, this);
    dialog_fireStaff->show();
    connect(dialog_fireStaff, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_addPersAbsence_clicked()
{
    Dialog_staffabsence* dialog_staffabsence = new Dialog_staffabsence(db, selectedStaffId, this);
    dialog_staffabsence->show();
}

void HR_department::on_button_printReport_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    QString queryText;
    QModelIndex index;
    int persId = selectedPersId;

    out << "<html>"
            << "<head>"
            << "<meta Content=\"Text/html; charset=utf-8\">"
            << QString("<title>%1</title>").arg("Report")
       << "</head>"
       << "<body bgcolor = #ffffff link=#5000A0>"
       << QString("<h2 align=center>%1</h2>").arg("Звіт працівника компанії")
       << "<br/>";



    //-------------
    // PERSINFO BLOCK
    //-------------

    queryText = QString("select * from \"Myronenko_O\".person where \"Id_person\" = %1;").arg(persId);
    QSqlQueryModel *modelPerson = db->getQueryModel(queryText);
    index = modelPerson->index(0, 1);
    QString name = index.data(Qt::DisplayRole).toString();
    index = modelPerson->index(0, 2);
    QString surname = index.data(Qt::DisplayRole).toString();
    index = modelPerson->index(0, 3);
    QString birthday = index.data(Qt::DisplayRole).toDate().toString("yyyy-MM-dd");
    index = modelPerson->index(0, 4);
    QString education = index.data(Qt::DisplayRole).toString();

    out << QString("<p>Ім'я: <b>%1</b></p>").arg(name)
       << QString("<p>Прізвище: <b>%1</b></p>").arg(surname)
       << QString("<p>Дата народження: <b>%1</b></p>").arg(birthday)
       << QString("<p>Освіта: <b>%1</b></p>").arg(education)
       << "<br/>";



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
    int rowCount = modelPersonSkills->rowCount();
    int columnCount = modelPersonSkills->columnCount();

    out << QString("<h4>%1</h4>").arg("Навички працівника:")
        << "<table border = 1 cellspacing=0 cellpadding=2 width=\"100%\">"
        << "<thead><tr bgcolo=#f0f0f0>";
    for( int column = 0; column < columnCount; column++)
        out << QString("<th>%1</th>").arg(modelPersonSkills->headerData(column,Qt::Horizontal).toString());
    out << "</tr></thead>";

    for (int row = 0; row < rowCount; row++ ) {
        out << "<tr>";
        for ( int column = 0; column < columnCount; column++){
            QString data = modelPersonSkills->data(modelPersonSkills->index(row,column)).toString().simplified();
            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
        out << "</tr>";
    }
    out << "</table><br/>";



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
    rowCount = modelWorkHistory->rowCount();
    columnCount = modelWorkHistory->columnCount();
    out << QString("<h4>%1</h4>").arg("Історія працевлаштування:")
        << "<table border = 1 cellspacing=0 cellpadding=2 width=\"100%\">"
        << "<thead><tr bgcolo=#f0f0f0>";
    for( int column = 0; column < columnCount; column++)
        out << QString("<th>%1</th>").arg(modelWorkHistory->headerData(column,Qt::Horizontal).toString());
    out << "</tr></thead>";

    for (int row = 0; row < rowCount; row++ ) {
        out << "<tr>";
        for ( int column = 0; column < columnCount; column++){
            QString data = modelWorkHistory->data(modelWorkHistory->index(row,column)).toString().simplified();
            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
        out << "</tr>";
    }
    out << "</table><br/>";



    out << "</body>\n </html>\n";
    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);
    if (DEBUGMODE) qDebug() << strStream << endl;
    QPrinter printer;

    printer.setOutputFormat(QPrinter::PdfFormat);
    QPrintDialog *dialog = new QPrintDialog(&printer,0);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }
    delete document;
}



//-----------
// VACANCIES TAB
//-----------

void HR_department::showVacTable()
{
    QString queryText =
            "select * from \"Myronenko_O\".show_vacancies;";
    QSqlQueryModel *model = db->getQueryModel(queryText);

    model->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(1, Qt::Horizontal, tr("Кількість вакантних місць"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_vacancies->setModel(proxyModel);
    ui->table_vacancies->setSortingEnabled(true);
    ui->table_vacancies->resizeColumnsToContents();
    ui->table_vacancies->setColumnHidden(2, true);
    for (int c = 0; c < ui->table_vacancies->horizontalHeader()->count(); ++c)
    {
        ui->table_vacancies->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void HR_department::on_button_closeWindow_3_clicked()
{
    return_to_dialogentry();
}

void HR_department::on_table_vacancies_pressed(const QModelIndex &index)
{
    int row = index.row();
    selectedVacId = index.sibling(row, 2).data().toInt();
    selectedVacName = index.sibling(row, 0).data().toString();
    int selectedVacCount = index.sibling(row, 1).data().toInt();
    if (selectedVacCount == 0) {
        ui->button_closeVacancy->setDisabled(true);
    } else {
        ui->button_closeVacancy->setEnabled(true);
    }
}

void HR_department::on_button_closeVacancy_clicked()
{
    Dialog_removeVacancy* dialog_removeVacancy = new Dialog_removeVacancy(db, selectedVacId, selectedVacName, this);
    dialog_removeVacancy->show();
    connect(dialog_removeVacancy, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_openVacancy_clicked()
{
    Dialog_openVacancy* dialog_openVacancy = new Dialog_openVacancy(db, this);
    dialog_openVacancy->show();
    connect(dialog_openVacancy, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_updateVacanciesTable_clicked()
{
    showVacTable();
}





//---------------
// POSITIONS TAB
//---------------

void HR_department::showPositTable()
{
    QString queryText =
            "select * from \"Myronenko_O\".show_positions;";
    QSqlQueryModel *model = db->getQueryModel(queryText);

    model->setHeaderData(0, Qt::Horizontal, tr("Посада"));
    model->setHeaderData(1, Qt::Horizontal, tr("Кількість робітників"));

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->table_positions->setModel(proxyModel);
    ui->table_positions->setSortingEnabled(true);
    ui->table_positions->resizeColumnsToContents();
    ui->table_positions->setColumnHidden(2, true);
    for (int c = 0; c < ui->table_positions->horizontalHeader()->count(); ++c)
    {
        ui->table_positions->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
}

void HR_department::on_table_positions_pressed(const QModelIndex &index)
{
    int row = index.row();
    selectedPositId = index.sibling(row, 2).data().toInt();
    ui->button_showPositInfo->setEnabled(true);
    if (db->getUser() == "admin")
    {
        ui->button_editPosition->setEnabled(true);
        int selectedPositStaffCount = index.sibling(row, 1).data().toInt();
        if (selectedPositStaffCount == 0) {
            ui->button_deletePosition->setEnabled(true);
        } else {
            ui->button_deletePosition->setDisabled(true);
        }
    } else {
        ui->button_editPosition->setDisabled(true);
        ui->button_deletePosition->setDisabled(true);
    }
}

void HR_department::on_button_editPosition_clicked()
{
    Dialog_editPosition* dialog_editPosition = new Dialog_editPosition(db, selectedPositId, this);
    dialog_editPosition->show();
    connect(dialog_editPosition, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_addPosition_clicked()
{
    Dialog_editPosition* dialog_addPosition = new Dialog_editPosition(db, -1, this);
    dialog_addPosition->show();
    connect(dialog_addPosition, SIGNAL(accepted()), this, SLOT(showAllTables()));
}

void HR_department::on_button_closeWindow_2_clicked()
{
    return_to_dialogentry();
}

void HR_department::on_updatePositTable_clicked()
{
    showPositTable();
}

void HR_department::on_button_deletePosition_clicked()
{
    qDebug() << "selectedPositId:" << selectedPositId << endl;
    QString queryText = QString("select \"Myronenko_O\".delete_position(%1);").arg(selectedPositId);
    db->executeQuery(queryText, "admin", this, 3);
    showPositTable();
}

void HR_department::on_button_showPositInfo_clicked()
{
    Dialog_showPositInfo* dialog_showPositInfo = new Dialog_showPositInfo(db, selectedPositId, this);
    dialog_showPositInfo->show();
}
