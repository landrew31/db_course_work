#include "db_setup.h"

DB_setup::DB_setup()
{
    connected = false;
}

DB_setup::~DB_setup()
{}

bool DB_setup::connect_to_db(QWidget* qwidget)
{
    base = QSqlDatabase::addDatabase("QPSQL");
    base.setHostName("52.24.64.65");
    base.setPort(5432);
    base.setDatabaseName("db_work");
    base.setUserName(user);
    base.setPassword(password);

    //qDebug() << "username: " << user << ", pass: " << password << endl;
    bool connectioncheck = base.open();
    connected = connectioncheck;
    if (connectioncheck == true){
        qDebug() << "Connection to database established." << endl;
    } else {
        qDebug() << "Error for database " << base.databaseName() << " :" << base.lastError().text() << endl;
        QMessageBox::about(qwidget, "Помилка", "Не вдалося увійти. Перевірте, будь ласка, ім'я та пароль.");
    }
    return connectioncheck;
}

bool DB_setup::getConnected()
{
    return connected;
}

QString DB_setup::getUser()
{
    return user;
}

QString DB_setup::getPassword()
{
    return password;
}

//QSqlDatabase DB_setup::getBase()
//{
//    return base;
//}

void DB_setup::setUser(QString user)
{
    this->user = user;
}

void DB_setup::setPassword(QString password)
{
    this->password = password;
}

QSqlQueryModel* DB_setup::getQueryModel(QString queryText)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    //base.open();
    QSqlQuery query = base.exec(queryText);
    query.first();
    //QString result = query.record().value(0).toString();
    //query->exec();
    model->setQuery(query);
    //qDebug() << result;
    return model;
}

 bool DB_setup::executeQuery(QString queryText, QString executer, QWidget* qwidget)
 {
     QSqlQuery query;
     query.prepare(queryText);
     bool executed = query.exec();
     qDebug() << executed << (user == executer )<< endl;
     if (!executed && user != executer) {
         QMessageBox::about(qwidget, "Помилка", "Вибачте, у Вас немає прав для даної операції.");
     } else if (!executed){
         QMessageBox::about(qwidget, "Помилка", "Введіть, будь ласка, коректні дані.");
     } else {
         QMessageBox::about(qwidget, "Сповіщення", "Дані додано. Ви можете оновити відображення.");
     };
     return executed;
 }
