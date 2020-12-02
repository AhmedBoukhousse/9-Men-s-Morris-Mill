#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>
#include "windialog.h"
#include "board.h"
#include "move.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QPushButton* button;
    ~MainWindow();
    Board gameBoard;
    Move AI;

private slots:
   void handleButton2(int button);

private:
    void setBlack(int button);
    void setRed(int button);
    void setEmpty(int button);
    void setTurnButton(char color);
    void movePiece(int player, int start, int dest);
    void updateBoard();
    void makeClickable(int pid);
    int millCheck(int newPiece);
    void isGameEnd();

    QIcon redIcon;
    QIcon blackIcon;
    QIcon blankIcon;
    QPushButton* PB[24];
    QSignalMapper *signalMapper;
    Ui::MainWindow *ui;
    winDialog *whowon;
    bool toggle = true;

    int prevGameState;
    int red = 9;
    int black = 9;
    int gameState = 1;
    int startSlot = 4822;
    int endSlot= 4822;
    int whoMilled;
    int playMode;
    bool AIMode = true;
};
#endif // MAINWINDOW_H
