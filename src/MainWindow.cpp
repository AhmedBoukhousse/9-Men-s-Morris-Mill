#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    prevGameState = 1;
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

    for (int i =0; i<BOARD_SIZE; i++)
    {
        connect(PB[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(PB[i], i);
    }

    setWindowTitle(tr("Nine Men's Morris"));
    ui->turnBox->setEnabled(false);
    setTurnButton('r');
    whowon = new winDialog();
}

void MainWindow::setBlack(int button)
{
    PB[button]->setIcon(blackIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.addPiece(BLACK_ID, button);
}

void MainWindow::setRed(int button)
{
    PB[button]->setIcon(redIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(false);
    gameBoard.addPiece(RED_ID, button);
}

void MainWindow::setEmpty(int button)
{
    gameBoard.removePiece(button);
    if (gameBoard.boardArea[button] == 0)
    {
    PB[button]->setIcon(blankIcon);
    PB[button]->setIconSize(QSize(65, 65));
    PB[button]->setEnabled(true);
    }
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
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (gameBoard.boardArea[i] == 0)
            setEmpty(i);
        else if (gameBoard.boardArea[i] == RED_ID)
            setRed(i);
        else if (gameBoard.boardArea[i] == BLACK_ID)
            setBlack(i);
    }
}

int MainWindow::millCheck(int newPiece)
{
    if (newPiece == 4822)
    {
        return 0;
    }

    int playerMill = gameBoard.checkMill(newPiece);
    if (playerMill == 1)
    {
        ui->textEdit->setText(tr("Red HAS A MILL"));
        prevGameState = gameState;
        if (AIMode == false)
            setTurnButton('r');
        makeClickable(BLACK_ID);
        gameState = 3;
    }
    if (playerMill == 2 && AIMode == true)
    {
        int remover = AI.AIRemovePiece(gameBoard);
        setEmpty(remover);
        AI.updateHumanVectors(-1, remover, gameBoard);
        updateBoard();
        return playerMill;
    }
    if (playerMill == 2 && AIMode == false)
    {
        ui->textEdit->setText(tr("Black HAS A MILL"));
        prevGameState = gameState;
        setTurnButton('b');
        makeClickable(RED_ID);
        gameState = 3;
    }
    return playerMill;
}

void MainWindow::isGameEnd()
{
    int scenario = gameBoard.GameOver();
    switch (scenario)
    {
    case 1:
        ui->textEdit->setText(tr("Red locked"));
        whowon->whoWonText(1);
        whowon->show();
        this->close();
        break;

    case 2:
        ui->textEdit->setText(tr("Black locked"));
        whowon->whoWonText(2);
        whowon->show();
        this->close();
        break;

    case 3:
        whowon->whoWonText(3);
        whowon->show();
        this->close();
        break;

    case 4:
        whowon->whoWonText(4);
        whowon->show();
        this->close();
        break;

    case 5:
        break;
    }
}

void MainWindow::makeClickable(int pid)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (pid == RED_ID)
        {
            if (gameBoard.boardArea[i] == EMPTY_ID)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == RED_ID)
                PB[i]->setEnabled(true);
            else if (gameBoard.boardArea[i] == BLACK_ID)
                PB[i]->setEnabled(false);
        }
        if (pid == BLACK_ID)
        {
            if (gameBoard.boardArea[i] == EMPTY_ID)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == RED_ID)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == BLACK_ID)
                PB[i]->setEnabled(true);
        }
        if (pid == EMPTY_ID)
        {
            if (gameBoard.boardArea[i] == EMPTY_ID)
                PB[i]->setEnabled(true);
            else if (gameBoard.boardArea[i] == RED_ID)
                PB[i]->setEnabled(false);
            else if (gameBoard.boardArea[i] == BLACK_ID)
                PB[i]->setEnabled(false);
        }
    }
}

void MainWindow::movePieceGUI(int player, int start, int dest)
{
    gameBoard.movePiece(player,start,dest);
    updateBoard();
}

void MainWindow::handleButton2(int button)
{
    if (AIMode == true)
    {
        if (gameState == 3) //piece removal state
        {
            setEmpty(button);
            AI.updateAIVectors(-1, button, gameBoard);
            if (gameBoard.boardArea[button] != EMPTY_ID)
            {
                ui->textEdit->setText(tr("that piece is in a mill, try again!"));
                return;
            }
            startSlot = 4822;
            endSlot = 4822;
            gameState = prevGameState;
            if (prevGameState == 2)
            {
                isGameEnd();
                ui->textEdit->setText(tr("Time to move pieces"));

                //AI Movement
                if (gameBoard.playerPiecesAmt[BLACK_ID] == 3)
                    AISwap = AI.AIFlyPiece(gameBoard);
                else
                    AISwap = AI.AIMovePiece(gameBoard);
                movePieceGUI(BLACK_ID, AISwap.first, AISwap.second);
                updateBoard();
                AI.updateAIVectors(AISwap.first, AISwap.second, gameBoard);
                whoMilled = millCheck(AISwap.second);

                makeClickable(RED_ID);
            }
            if (prevGameState == 1)
            {
                ui->textEdit->setText(tr("Time to add pieces"));

                //AI Addition
                if(black > 0)
                {
                int AIPos = AI.AIPlacePiece(gameBoard);
                setBlack(AIPos);
                AI.updateAIVectors(AIPos, -1, gameBoard);
                updateBoard();
                whoMilled = millCheck(AIPos);
                black--;
                }
                makeClickable(EMPTY_ID);
            }
            return;
        }
        if (gameState == 1) //adding piece state
        {
            if (red > 0)
            {
                //Player Addition
                setRed(button);
                updateBoard();
                whoMilled = millCheck(button);
                if (whoMilled == RED_ID)
                    return;
                red--;

                //AI Addition
                if(black > 0)
                {
                AI.updateHumanVectors(button, -1, gameBoard);
                int AIPos = AI.AIPlacePiece(gameBoard);
                setBlack(AIPos);
                AI.updateAIVectors(AIPos, -1, gameBoard);
                updateBoard();
                whoMilled = millCheck(AIPos);
                black--;
                }
            }
            if (red == 0 && black == 0)
            {
                gameState = 2;
                whoMilled = millCheck(button);
                isGameEnd();
                makeClickable(RED_ID);
                ui->textEdit->setText(tr("Time to move pieces"));
                return;
            }
            return;
        }
        if (gameState == 2) //move piece state
        {
            if (toggle == true)
            {
                if (startSlot == 4822)
                {
                    startSlot = button;
                    makeClickable(EMPTY_ID);
                    return;
                }
                else
                {
                    endSlot = button;
                    movePieceGUI(RED_ID, startSlot, endSlot);
                    AI.updateHumanVectors(startSlot, endSlot, gameBoard);
                    if(gameBoard.checkAdjacent(startSlot,endSlot) || gameBoard.playerPiecesAmt[RED_ID] == 3)
                    {
                        //Player Movement
                        whoMilled = millCheck(endSlot);
                        if(whoMilled == RED_ID)
                            return;

                        //AI Movement
                        if (gameBoard.playerPiecesAmt[BLACK_ID] == 3)
                            AISwap = AI.AIFlyPiece(gameBoard);
                        else
                            AISwap = AI.AIMovePiece(gameBoard);
                        movePieceGUI(BLACK_ID, AISwap.first, AISwap.second);
                        updateBoard();
                        AI.updateAIVectors(AISwap.first, AISwap.second, gameBoard);
                        whoMilled = millCheck(AISwap.second);

                        //Turn end
                        startSlot = 4822;
                        endSlot = 4822;
                        isGameEnd();
                        makeClickable(RED_ID);
                    }
                    else
                    {
                        //Invalid Move
                        ui->textEdit->setText(tr("Illegal move, reselect a piece"));
                        startSlot = 4822;
                        endSlot = 4822;
                        makeClickable(RED_ID);
                    }
                    return;
                }
            }
        }
    }

    if (AIMode == false)
    {
        if (gameState == 3) //piece removal state
        {
            setEmpty(button);
            if (gameBoard.boardArea[button] != 0)
            {
                ui->textEdit->setText(tr("that piece is in a mill, try again!"));
                return;
            }
            if (whoMilled == RED_ID)
            {
                toggle = false;
                makeClickable(BLACK_ID);
                setTurnButton('b');
            }
            else if (whoMilled == BLACK_ID)
            {
                toggle = true;
                makeClickable(RED_ID);
                setTurnButton('r');
            }
            startSlot = 4822;
            endSlot = 4822;
            gameState = prevGameState;
            if (prevGameState == 2)
            {
                isGameEnd();
                ui->textEdit->setText(tr("Time to move pieces"));
            }
            if (prevGameState == 1)
            {
                ui->textEdit->setText(tr("Time to add pieces"));
                makeClickable(EMPTY_ID);
            }
            return;
        }
        if (gameState == 1) //adding piece state
        {
            if (toggle == true && red > 0)
            {
                setTurnButton('b');
                setRed(button);
                updateBoard();
                whoMilled = millCheck(button);
                toggle=false;
                red--;
            }
            else if (toggle == false && black > 0)
            {
                setTurnButton('r');
                setBlack(button);
                updateBoard();
                whoMilled = millCheck(button);
                toggle=true;
                black--;
            }
            if (red == 0 && black == 0)
            {
                gameState = 2;
                whoMilled = millCheck(button);
                isGameEnd();
                makeClickable(RED_ID);
                ui->textEdit->setText(tr("Time to move pieces"));
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
                    makeClickable(EMPTY_ID);
                    return;
                }
                else
                {
                    endSlot = button;
                    movePieceGUI(RED_ID, startSlot, endSlot);
                    if(gameBoard.checkAdjacent(startSlot,endSlot) || gameBoard.playerPiecesAmt[RED_ID] == 3)
                    {
                        setTurnButton('b');
                        whoMilled = millCheck(endSlot);
                        startSlot = 4822;
                        endSlot = 4822;
                        toggle = false;
                        isGameEnd();
                        makeClickable(BLACK_ID);
                    }
                    else
                    {
                        ui->textEdit->setText(tr("Illegal move, reselect a piece"));
                        startSlot = 4822;
                        endSlot = 4822;
                        makeClickable(RED_ID);
                    }
                    return;
                }
            }
            if (toggle == false)
            {
                if (startSlot == 4822)
                {
                    startSlot = button;
                    makeClickable(EMPTY_ID);
                    return;
                }
                else
                {
                    endSlot = button;
                    movePieceGUI(BLACK_ID, startSlot, endSlot);
                    if(gameBoard.checkAdjacent(startSlot,endSlot) || gameBoard.playerPiecesAmt[BLACK_ID] == 3)
                    {
                        setTurnButton('r');
                        whoMilled = millCheck(endSlot);
                        startSlot = 4822;
                        endSlot = 4822;
                        isGameEnd();
                        toggle = true;
                        makeClickable(RED_ID);
                    }
                    else
                    {
                        ui->textEdit->setText(tr("Illegal move, reselect a piece"));
                        startSlot = 4822;
                        endSlot = 4822;
                        makeClickable(BLACK_ID);
                    }
                    return;
                }
            }
        }
  }
}

MainWindow::~MainWindow()
{
    delete ui;
}

