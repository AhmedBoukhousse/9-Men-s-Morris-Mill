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
        ui->winText->setText("Player 1 has no legal moves left. Player 2 Wins!");
        break;
        case 2:
        ui->winText->setText("Player 2 has no legal moves left. Player 1 Wins!");
        break;
        case 3:
        ui->winText->setText("Player 1 has only 2 pieces left. Player 2 Wins!");
        break;
        case 4:
        ui->winText->setText("Player 2 has only 2 pieces left. Player 1 Wins!");
        break;
    }

}
