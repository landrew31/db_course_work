#ifndef DIALOG_ADDSKILL_H
#define DIALOG_ADDSKILL_H

#include <QObject>
#include "db_setup.h"

namespace Ui {
class Dialog_addSkill;
}

class Dialog_addSkill : public QDialog
{
    Q_OBJECT

public:
    Dialog_addSkill(DB_setup* db = 0, QWidget *parent = 0);
    ~Dialog_addSkill();

private slots:
    void accept();

};

#endif // DIALOG_ADDSKILL_H
