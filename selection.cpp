#include "selection.h"
#include "ui_selection.h"
Selection::Selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selection)
{
    ui->setupUi(this);
    setWindowTitle(tr("Player Selection"));
    //onePlayer.addPixmap(QPixmap(":/images/1p.png"), QIcon::Normal);
   // onePlayer.addPixmap(QPixmap(":/images/1p.png"), QIcon::Disabled);

    //twoPlayer.addPixmap(QPixmap(":/images/2p.png"), QIcon::Normal);
    //twoPlayer.addPixmap(QPixmap(":/images/2p.png"), QIcon::Disabled);
}

Selection::~Selection()
{
    delete ui;
}
