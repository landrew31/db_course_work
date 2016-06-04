#ifndef HR_DEPARTMENT_H
#define HR_DEPARTMENT_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
#include <QModelIndex>
#include <QDebug>
#include "QtPrintSupport/QPrinter"
#include <QtPrintSupport/QPrintDialog>

#include "db_setup.h"
#include "functions.h"
#include "ui_hr_department.h"

#include "dialog_showstaffprofile.h"
#include "dialog_editpersinfo.h"
#include "dialog_changeposition.h"
#include "dialog_addstaff.h"
#include "dialog_firestaff.h"
#include "dialog_staffabsence.h"

#include "dialog_removevacancy.h"
#include "dialog_openvacancy.h"

#include "dialog_editposition.h"
#include "dialog_showpositinfo.h"

#define DEBUGMODE true


namespace Ui {
class HR_department;
}

class HR_department : public QMainWindow
{
    Q_OBJECT

public:
    explicit HR_department(DB_setup *db = 0, QWidget *parent = 0);
    ~HR_department();

private:
    Ui::HR_department *ui;
    DB_setup *db;

    int selectedPersId, selectedStaffId, selectedPositId, selectedVacId;
    QString selectedVacName;

private slots:
    void showStaffTable();
    void showPositTable();
    void showVacTable();
    void showAllTables();

private slots:
    void on_table_staff_pressed(const QModelIndex &index);
    void on_button_editPersInfo_clicked();
    void on_button_addStuff_clicked();
    void on_date_historyView_dateChanged();
    void on_button_closeWindow_clicked();
    void on_button_closeWindow_3_clicked();
    void on_table_positions_pressed(const QModelIndex &index);
    void on_button_editPosition_clicked();
    void on_button_addPosition_clicked();
    void on_button_closeWindow_2_clicked();
    void on_table_vacancies_pressed(const QModelIndex &index);
    void on_button_closeVacancy_clicked();
    void on_updateVacanciesTable_clicked();
    void on_updatePositTable_clicked();
    void on_updateStaffTable_clicked();
    void on_button_openVacancy_clicked();
    void on_button_deletePosition_clicked();
    void on_button_showPositInfo_clicked();
    void on_button_showPersInfo_clicked();
    void on_button_changePersPosition_clicked();
    void on_button_firePers_clicked();
    void on_button_addPersAbsence_clicked();
    void on_button_printReport_clicked();
    void return_to_dialogentry();
};

#endif // HR_DEPARTMENT_H
