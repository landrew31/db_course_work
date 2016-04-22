#include "dialogentry.h"
#include <QApplication>
/* фів*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogEntry* entry = new DialogEntry();

    entry->show();

    return a.exec();
}
