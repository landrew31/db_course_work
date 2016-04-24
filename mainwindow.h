#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateEdit>
//#include <QDebug>
//#include <QMessageBox>

#include "db_setup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DB_setup *db = 0, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_renew_actions_button_clicked();
    void on_add_action_button_clicked();

private:
    Ui::MainWindow *ui;
    DB_setup *db;
};

#endif // MAINWINDOW_H
