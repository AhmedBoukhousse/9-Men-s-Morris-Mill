#include "selection.h"
#include "ui_selection.h"

selection::selection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selection)
{
    ui->setupUi(this);
    setWindowTitle(tr("Player Selection"));
    connect (ui->onePlayer, SIGNAL(clicked()), this, SLOT(on_onePlayer_clicked));
    connect (ui->twoPlayer, SIGNAL(clicked()), this, SLOT(on_twoPlayer_clicked));
}

void selection::openGameBoard()
{
    gameBoard = new MainWindow();
    gameBoard->show();
    this->close();
}

void selection::openNotReady()
{
    notreadydialog = new notready();
    notreadydialog->show();
}

void selection::on_onePlayer_clicked()
{
    openGameBoard();
}

void selection::on_twoPlayer_clicked()
{
    openNotReady();
}

selection::~selection()
{
    delete ui;
}
