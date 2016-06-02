#ifndef DIALOG_CHANGEPOSITION_H
#define DIALOG_CHANGEPOSITION_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_changePosition;
}

class Dialog_changePosition : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_changePosition(DB_setup* db = 0, int selectedStaffId = 0, int selectedPersId = 0, QWidget *parent = 0);
    ~Dialog_changePosition();

private slots:
    void showInpValues();
    void updatePositSelect();
    void on_openNewVacancy_clicked();
    void accept();

private:
    Ui::Dialog_changePosition *ui;
    DB_setup* db;
    int staffId, persId;
    QSqlQueryModel* modelAllOpenedVacs;
};

#endif // DIALOG_CHANGEPOSITION_H
