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
