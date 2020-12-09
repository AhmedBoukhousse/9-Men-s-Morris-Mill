#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>
#include "windialog.h"
#include "board.h"
#include "computerPlayer.h"

#define MORRIS_AMT 9 //amount of pieces a player has
#define RED_ID 1 //ID of the Red piece
#define BLACK_ID 2 //ID of the Black piece
#define EMPTY_ID 0 //ID of an empty spot
#define BOARD_SIZE 24 //amount of spaces on the board

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool AIMode;
    QPushButton* button;
    ~MainWindow();
    Board gameBoard;
    computerPlayer AI;

private slots:
   void handleButton2(int button);

private:

   //GUI set pieces on board
    void setBlack(int button);
    void setRed(int button);
    void setEmpty(int button);
    void setTurnButton(char color);

    //shortcut functions with calls to board to lower code amount
    void movePieceGUI(int player, int start, int dest);
    int millCheck(int newPiece);
    void isGameEnd();

    //updates GUI based on values of board Object
    void updateBoard();

    //makes buttons of a certain type clickable for player
    void makeClickable(int pid);

    //used to select pieces for AI to move
    pair<int,int> AISwap = make_pair(0,0);

    //Qt related vars
    QIcon redIcon;
    QIcon blackIcon;
    QIcon blankIcon;
    QPushButton* PB[24];
    QSignalMapper *signalMapper;
    Ui::MainWindow *ui;
    winDialog *whowon;
    bool toggle = true;

    //Variables related in turn logic
    int prevGameState;
    int red = MORRIS_AMT;
    int black = MORRIS_AMT;
    int gameState = 1;
    int startSlot = 4822;
    int endSlot = 4822;
    int whoMilled;
};
#endif // MAINWINDOW_H
