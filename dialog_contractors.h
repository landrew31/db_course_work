#ifndef DIALOG_CONTRACTORS_H
#define DIALOG_CONTRACTORS_H

#include <QDialog>

namespace Ui {
class Dialog_contractors;
}

class Dialog_contractors : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_contractors(QWidget *parent = 0);
    ~Dialog_contractors();

private:
    Ui::Dialog_contractors *ui;
};

#endif // DIALOG_CONTRACTORS_H
