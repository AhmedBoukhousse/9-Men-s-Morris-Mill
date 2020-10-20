#ifndef BOARD_H
#define BOARD_H

#include "player.h"
#include <map>
class Board
{
public:
    Board();
    int boardArea[24];
    //Player player1(1);
    //Player player2;
    bool flightMode = false;
    map<int, int> playerPieces;
    int checkMill();
    bool checkAdjacent(int origin, int dest);
    int collCheck(int i, int j, int k);
    void addPiece(int pid, int slot);
    void removePiece(int slot);
    void swapPiece(int pid, int origin, int dest);
    int colls[24] = {0,9,21,3,10,18,6,11,15,1,4,7,16,19,22,8,12,17,5,13,21,2,14,23};
    int adjacent[64] =
    {
        0,1,
        0,9,
        1,2,
        1,4,
        2,14,
        3,10,
        3,4,
        4,5,
        4,7,
        5,13,
        6,7,
        6,11,
        7,8,
        8,12,
        9,10,
        9,21,
        10,11,
        10,18,
        11,15,
        12,13,
        12,17,
        13,14,
        13,20,
        14,23,
        15,16,
        16,17,
        16,19,
        18,19,
        19,20,
        19,22,
        21,22,
        22,23
    };
};

#endif // BOARD_H
