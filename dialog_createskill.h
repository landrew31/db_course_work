#ifndef DIALOG_CREATESKILL_H
#define DIALOG_CREATESKILL_H

#include <QDialog>
#include "db_setup.h"
#include "functions.h"

#define DEBUGMODE true
#define UNSECURE false
#define UNSECURE_DEP 2
//#include "hr_department.h"

namespace Ui {
class Dialog_createSkill;
}

class Dialog_createSkill : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_createSkill(DB_setup* db = 0, QWidget *parent = 0);
    ~Dialog_createSkill();

private slots:
    void accept();

private:
    Ui::Dialog_createSkill *ui;
    DB_setup *db;
};

#endif // DIALOG_CREATESKILL_H
