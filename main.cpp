#include "dialogentry.h"
#include <QApplication>
#include "db_setup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DB_setup* db = new DB_setup();
    DialogEntry* entryWindow = new DialogEntry(db);
    if (!UNSECURE) entryWindow->show();

    return a.exec();
}
