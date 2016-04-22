#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogentry.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDB(QString user_got, QString password_got){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("52.24.64.65");
    db.setPort(5432);
    db.setDatabaseName("db_work");
    user = user_got;
    password = password_got;
    db.setUserName(user);
    db.setPassword(password);

    bool connectioncheck = db.open();
    if (connectioncheck == true){
        qDebug() << "Connection to database established." << endl;
    } else {
        qDebug() << "Error for database " << db.databaseName() << " :" << db.lastError().text() << endl;
        QMessageBox::about(this, "Помилка", "Не вдалося увійти. Перевірте, будь ласка, ім'я та пароль.");
    }
}


void MainWindow::on_renew_actions_button_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
//    db.open();
    QSqlQuery query = db.exec("select day_start, day_stop, percent from \"Lupa_A\".actions;");
    query.first();
    QString result = query.record().value(0).toString();
    //query->exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Початок акції"));
    model->setHeaderData(1, Qt::Horizontal, tr("Кінець акції"));
    model->setHeaderData(2, Qt::Horizontal, tr("Відсоток по акції"));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);

    qDebug() << result;
}


void MainWindow::on_add_action_button_clicked()
{
    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
    int percent = ui->action_percent_field->text().toInt();

    qDebug() << start << stop << percent;

    QSqlQuery query;
    query.prepare("insert into \"Lupa_A\".actions (day_start, day_stop, percent) values('"+ start + "','" + stop + "', :percent);");
    query.bindValue(":percent", percent);
    bool executed = query.exec();
    qDebug() << executed << (user == "operator" )<< endl;
    if (!executed && user == "operator") {
        QMessageBox::about(this, "Помилка", "Вибачте, у Вас немає прав для даної операції.");
    } else if (!executed){

        QMessageBox::about(this, "Помилка", "Введіть, будь ласка, коректні дані.");
    } else {
        QMessageBox::about(this, "Сповіщення", "Дані додано. Ви можете оновити відображення.");
    }
}
