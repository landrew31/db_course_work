#include "functions.h"

bool inQStringList(QString item, QStringList list) {
    if (list.length() == 0){
        return false;
    }
    for(QStringList::iterator it = list.begin(); it != list.end(); ++it) {
        QString current = *it;
        if (current == item){
            return true;
        }
    }
    return false;
}

int searchIdByNameInModel(QString key, QSqlQueryModel* model, int idPosit, int keyPosit)
{
    int id = -1;
    QModelIndex index;
    int rowCount = model->rowCount();
    for (int i=0; i < rowCount; i++)
    {
        index = model->index(i, keyPosit);
        if ( key.compare(index.data(Qt::DisplayRole).toString()) == 0 )
        {
            index = model->index(i, idPosit);
            id = index.data(Qt::DisplayRole).toInt();
            break;
        }
    }
    return id;
}
