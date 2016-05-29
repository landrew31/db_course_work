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
    QSqlQuery query = base.exec(queryText);
    //qDebug() << query.lastError();
    query.first();
    //QString result = query.record().value(0).toString();
    //query->exec();
    model->setQuery(query);
    //qDebug() << result;
    return model;
}

bool DB_setup::executeQuery(QString queryText, QString executer, QWidget* qwidget, int queryType)
 {
     QSqlQuery query;
     query.prepare(queryText);
     bool executed = query.exec();
     if (!executed && user == executer) {
         showMessage("Помилка", "Вибачте, у Вас немає прав для даної операції.");
     } else if (!executed){
         showMessage("Помилка", "Введіть, будь ласка, коректні дані.");
     } else {
         switch (queryType){
         case 0:
            showMessage("Сповіщення", "Дані отримано.");
            break;
         case 1:
            showMessage("Сповіщення", "Дані додано.");
            break;
         case 2:
            showMessage("Сповіщення", "Дані оновлено.");
            break;
         case 3:
            showMessage("Сповіщення", "Дані видалено.");
            break;
         default:
            showMessage("Сповіщення", "Опрерація пройшла успішно.");
         }
     };
     return executed;
 }

 void DB_setup::showMessage(QString title, QString text)
 {
     MessageBox msgBox;
     msgBox.setWindowTitle(title);
     msgBox.setText(text);
     msgBox.setIcon(QMessageBox::Information);
     msgBox.setStandardButtons(QMessageBox::Ok);
     msgBox.setButtonText(QMessageBox::Ok, "OK (До закриття: 10 с)");
     msgBox.setAutoClose(true);
     msgBox.setTimeout(10); //Closes after ten seconds
     msgBox.exec();
 }

void DB_setup::table_column_entire_width(QTableView *table)
{
     for (int c = 0; c < table->horizontalHeader()->count(); ++c)
     {
         table->horizontalHeader()->setSectionResizeMode(
                     c, QHeaderView::Stretch);
     }
 }
