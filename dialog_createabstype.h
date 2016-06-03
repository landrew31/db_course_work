#ifndef DIALOG_CREATEABSTYPE_H
#define DIALOG_CREATEABSTYPE_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_createAbsType;
}

class Dialog_createAbsType : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_createAbsType(DB_setup* db = 0, QWidget *parent = 0);
    ~Dialog_createAbsType();

private slots:
    void accept();

private:
    Ui::Dialog_createAbsType *ui;
    DB_setup *db;
};

#endif // DIALOG_CREATEABSTYPE_H
