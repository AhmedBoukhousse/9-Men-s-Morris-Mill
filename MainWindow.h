#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>
#include "board.h"

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
    int prevGameState;
    Ui::MainWindow *ui;
    bool toggle = true;
    QPushButton* PB[24];
    QSignalMapper *signalMapper;
    int red = 9;
    int black = 9;
    int gameState = 1;
    int startSlot = 4822;
    int endSlot= 4822;
    int whoMilled;
    QIcon redIcon;
    QIcon blackIcon;
    QIcon blankIcon;
};
#endif // MAINWINDOW_H
