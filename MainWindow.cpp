#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PB[0]=ui->a7;PB[1]=ui->d7;PB[2]=ui->g7;PB[3]=ui->b6;
    PB[4]=ui->d6;PB[5]=ui->f6;PB[6]=ui->c5;PB[7]=ui->d5;
    PB[8]=ui->e5;PB[9]=ui->a4;PB[10]=ui->b4;PB[11]=ui->c4;
    PB[12]=ui->e4;PB[13]=ui->f4;PB[14]=ui->g4;PB[15]=ui->c3;
    PB[16]=ui->d3;PB[17]=ui->e3;PB[18]=ui->b2;PB[19]=ui->d2;
    PB[20]=ui->f2;PB[21]=ui->a1;PB[22]=ui->d1;PB[23]=ui->g1;

    redIcon.addPixmap(QPixmap(":/images/red.png"), QIcon::Normal);
    redIcon.addPixmap(QPixmap(":/images/red.png"), QIcon::Disabled);

    blackIcon.addPixmap(QPixmap(":/images/black.png"), QIcon::Normal);
    blackIcon.addPixmap(QPixmap(":/images/black.png"), QIcon::Disabled);

    blankIcon.addPixmap(QPixmap(":/images/empty.png"), QIcon::Normal);
    blankIcon.addPixmap(QPixmap(":/images/empty.png"), QIcon::Disabled);

    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButton2(int)));

    for (int i =0; i<24; i++)
    {
        connect(PB[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(PB[i], i);
    }
    setWindowTitle(tr("Nine Men's Morris"));
}

void MainWindow::setBlack(int button)
{
    PB[button]->setIcon(blackIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.boardArea[button] = 2;
}

void MainWindow::setRed(int button)
{
    PB[button]->setIcon(redIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.boardArea[button] = 1;
}

void MainWindow::setEmpty(int button)
{
    PB[button]->setIcon(blankIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(true);
    gameBoard.boardArea[button] = 0;
}

void MainWindow::handleButton2(int button)
{
    if (toggle == true && red > 0)
    {
        setRed(button);
        toggle=false;
        red--;
        //CheckForMills
    }
    else if (toggle == false && black > 0)
    {
        setBlack(button);
        toggle =true;
        black--;
        //CheckForMills
    }
 }


MainWindow::~MainWindow()
{
    delete ui;
}

