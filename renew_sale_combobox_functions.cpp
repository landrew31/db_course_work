#include "db_setup.h"
#include <QComboBox>


/* RENEW COMBOBOXES BLOCK */
void renew_action_on_program_comboBox(DB_setup* db, QComboBox* box)
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions ORDER BY action_name;");
    box->setModel(model);
    box->setCurrentIndex(-1);
}

void renew_contr_on_card_comboBox(DB_setup* db, QComboBox* box)
{
    QSqlQueryModel *model = db->getQueryModel("SELECT contr_name FROM \"Lupa_A\".contractors ORDER BY contr_name;");
    box->setModel(model);
    box->setCurrentIndex(-1);
}

void renew_program_on_card_comboBox(DB_setup* db, QComboBox* box)
{
    QSqlQueryModel *model = db->getQueryModel("SELECT program_name FROM \"Lupa_A\".action_programs ORDER BY program_name;");
    box->setModel(model);
    box->setCurrentIndex(-1);
}

void renew_action_on_card_comboBox(DB_setup* db, QComboBox* box)
{
    QSqlQueryModel *model = db->getQueryModel("SELECT action_name FROM \"Lupa_A\".actions ORDER BY action_name;");
    box->setModel(model);
    box->setCurrentIndex(-1);
}
/* END RENEW COMBOBOXES BLOCK */
