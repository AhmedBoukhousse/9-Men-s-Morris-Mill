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

    ui->textEdit->setText(tr("Time to add pieces"));

    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(handleButton2(int)));

    for (int i =0; i<24; i++)
    {
        connect(PB[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(PB[i], i);
    }
    setWindowTitle(tr("Nine Men's Morris"));
    ui->turnBox->setEnabled(false);
    setTurnButton('r');
}

void MainWindow::setBlack(int button)
{
    PB[button]->setIcon(blackIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.addPiece(2, button);
}

void MainWindow::setRed(int button)
{
    PB[button]->setIcon(redIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.addPiece(1, button);
}

void MainWindow::setEmpty(int button)
{
    PB[button]->setIcon(blankIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(true);
    gameBoard.removePiece(button);
}

void MainWindow::setTurnButton(char color)
{
    if(color == 'r')
        ui->turnBox->setIcon(redIcon);
    else if(color == 'b')
        ui->turnBox->setIcon(blackIcon);
    else
        ui->turnBox->setIcon(blackIcon);
    ui->turnBox->setIconSize(QSize(65, 65));
}

void MainWindow::updateBoard()
{
    for (int i = 0; i < 24; i++)
    {
        if (gameBoard.boardArea[i] == 0)
            setEmpty(i);
        else if (gameBoard.boardArea[i] == 1)
            setRed(i);
        else if (gameBoard.boardArea[i] == 2)
            setBlack(i);
    }
}

void MainWindow::millCheck()
{
    int playerMill = gameBoard.checkMill();
    if (playerMill == 1)
    {
        ui->textEdit->setText(tr("PLAYER 1 HAS A MILL"));
        //gameState = 3;
    }
    if (playerMill == 2)
    {
        ui->textEdit->setText(tr("PLAYER 2 HAS A MILL"));
        //gameState = 3;
    }
}

void MainWindow::makeClickable(int pid)
{
    for (int i = 0; i < 24; i++)
    {
        if (pid == 1)
        {
            if (gameBoard.boardArea[i] == 0)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == 1)
                PB[i]->setEnabled(true);
            else if (gameBoard.boardArea[i] == 2)
                PB[i]->setEnabled(false);
        }
        if (pid == 2)
        {
            if (gameBoard.boardArea[i] == 0)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == 1)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == 2)
                PB[i]->setEnabled(true);
        }
        if (pid == 3)
        {
            if (gameBoard.boardArea[i] == 0)
                PB[i]->setEnabled(true);
            else if (gameBoard.boardArea[i] == 1)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == 2)
                PB[i]->setEnabled(false);
        }
    }
}

void MainWindow::movePiece(int player, int start, int dest)
{
    gameBoard.swapPiece(player,start,dest);
    updateBoard();
}

void MainWindow::handleButton2(int button)
{
    if(gameState == 1) //adding piece state
    {
        if (toggle == true && red > 0)
        {
            setTurnButton('b');
            gameBoard.addPiece(1,button);
            updateBoard();
            toggle=false;
            red--;
            millCheck();

        }
        else if (toggle == false && black > 0)
        {
            setTurnButton('r');
            gameBoard.addPiece(2,button);
            updateBoard();
            toggle=true;
            black--;
            millCheck();
        }
        if (red == 0 && black == 0)
        {
            gameState = 2;
            ui->textEdit->setText(tr("Time to move pieces"));
            makeClickable(1);
            return;
        }
    }
    if (gameState == 2) //move piece state
    {
        if (toggle == true)
        {
            if (startSlot == 4822)
            {
                startSlot = button;
                makeClickable(3);
                return;
            }
            else
            {
                endSlot = button;
                movePiece(1, startSlot, endSlot);
                if(gameBoard.checkAdjacent(startSlot,endSlot))
                {
                    millCheck();
                    startSlot = 4822;
                    endSlot = 4822;
                    toggle = false;
                    makeClickable(2);
                    setTurnButton('b');
                }
                else
                {
                    ui->textEdit->setText(tr("Illegal move, reselect a piece"));
                    startSlot = 4822;
                    endSlot = 4822;
                    makeClickable(1);

                }
                return;
            }
        }
        if (toggle == false)
        {
            if (startSlot == 4822)
            {
                startSlot = button;
                makeClickable(3);
                return;
            }
            else
            {
                endSlot = button;
                movePiece(2, startSlot, endSlot);
                if(gameBoard.checkAdjacent(startSlot,endSlot))
                {
                    millCheck();
                    startSlot = 4822;
                    endSlot = 4822;
                    toggle = true;
                    makeClickable(1);
                    setTurnButton('r');
                }
                else
                {
                    ui->textEdit->setText(tr("Illegal move, reselect a piece"));
                    startSlot = 4822;
                    endSlot = 4822;
                    makeClickable(2);

                }
                return;
            }
        }
    }
    if (gameState == 3) //piece removal state
    {

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

