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

void table_column_entire_width(QTableView *table) {
    for (int c = 0; c < table->horizontalHeader()->count(); ++c)
    {
        table->horizontalHeader()->setSectionResizeMode(
                    c, QHeaderView::Stretch);
    }
}
