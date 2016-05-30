#ifndef DIALOG_SHOWPOSITINFO_H
#define DIALOG_SHOWPOSITINFO_H

#include <QDialog>
#include "hr_department.h"

namespace Ui {
class Dialog_showPositInfo;
}

class Dialog_showPositInfo : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_showPositInfo(DB_setup* db = 0, int selectedPositId = 0, QWidget *parent = 0);
    ~Dialog_showPositInfo();

private slots:
    void showInpValues();

private:
    Ui::Dialog_showPositInfo *ui;
    DB_setup* db;
    int positId;
};

#endif // DIALOG_SHOWPOSITINFO_H
