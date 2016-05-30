#ifndef DIALOG_OPENVACANCY_H
#define DIALOG_OPENVACANCY_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_openVacancy;
}

class Dialog_openVacancy : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_openVacancy(DB_setup* db = 0, QWidget *parent = 0);
    ~Dialog_openVacancy();

private slots:
    void showInpValues();

    void on_button_createPosition_clicked();

private:
    Ui::Dialog_openVacancy *ui;
    DB_setup *db;
    QSqlQueryModel* modelAllPositions;

    void accept();
};

#endif // DIALOG_OPENVACANCY_H
