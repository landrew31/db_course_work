#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogentry.h"

MainWindow::MainWindow(DB_setup *db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db = db;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_renew_actions_button_clicked()
{
    //QSqlQueryModel* model = db->getQueryModel("select day_start, day_stop, percent from \"Lupa_A\".actions;");

    QSqlQueryModel* model = new QSqlQueryModel();
    db->getBase().open();
    QSqlQuery query = db->getBase().exec("select day_start, day_stop, percent from \"Lupa_A\".actions;");
    query.first();
    QString result = query.record().value(0).toString();
    query.exec();
    model->setQuery(query);
    qDebug() << result;

    model->setHeaderData(0, Qt::Horizontal, tr("Початок акції"));
    model->setHeaderData(1, Qt::Horizontal, tr("Кінець акції"));
    model->setHeaderData(2, Qt::Horizontal, tr("Відсоток по акції"));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
}


void MainWindow::on_add_action_button_clicked()
{
//    QString start = ui->start_action_date->date().toString("yyyy-MM-dd");
//    QString stop = ui->stop_action_date->date().toString("yyyy-MM-dd");
//    int percent = ui->action_percent_field->text().toInt();

//    qDebug() << start << stop << percent;

//    QSqlQuery query;
//    query.prepare("insert into \"Lupa_A\".actions (day_start, day_stop, percent) values('"+ start + "','" + stop + "', :percent);");
//    query.bindValue(":percent", percent);
//    bool executed = query.exec();
//    qDebug() << executed << (db->getUser() == "operator" )<< endl;
//    if (!executed && db->getUser() == "operator") {
//        QMessageBox::about(this, "Помилка", "Вибачте, у Вас немає прав для даної операції.");
//    } else if (!executed){

//        QMessageBox::about(this, "Помилка", "Введіть, будь ласка, коректні дані.");
//    } else {
//        QMessageBox::about(this, "Сповіщення", "Дані додано. Ви можете оновити відображення.");
//    };
}
