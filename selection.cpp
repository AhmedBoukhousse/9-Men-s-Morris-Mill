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

void selection::on_onePlayer_clicked()
{
    gameBoard = new MainWindow();
    gameBoard->AIMode = true;
    gameBoard->show();
    this->close();
}

void selection::on_twoPlayer_clicked()
{
    gameBoard = new MainWindow();
    gameBoard->AIMode = false;
    gameBoard->show();
    this->close();
}

selection::~selection()
{
    delete ui;
}
