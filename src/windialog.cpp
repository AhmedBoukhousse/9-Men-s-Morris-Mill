#include "windialog.h"
#include "ui_windialog.h"

winDialog::winDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winDialog)
{
    ui->setupUi(this);
}

winDialog::~winDialog()
{
    delete ui;
}

void winDialog::whoWonText(int scenario)
{
    switch (scenario) {
        case 1:
        ui->winText->setText("Red has no legal moves left. Black Wins!");
        break;
        case 2:
        ui->winText->setText("Black has no legal moves left. Red Wins!");
        break;
        case 3:
        ui->winText->setText("Red has only 2 pieces left. Black Wins!");
        break;
        case 4:
        ui->winText->setText("Black has only 2 pieces left. Red Wins!");
        break;
    }

}
