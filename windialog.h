#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>

namespace Ui {
class winDialog;
}

class winDialog : public QDialog
{
    Q_OBJECT

public:
    explicit winDialog(QWidget *parent = nullptr);
    void whoWonText(int scenario);
    ~winDialog();

private:
    Ui::winDialog *ui;
};

#endif // WINDIALOG_H
