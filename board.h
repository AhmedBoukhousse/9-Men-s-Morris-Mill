#ifndef BOARD_H
#define BOARD_H


class Board
{
public:
    Board();
    int boardArea[24];
    int checkMill(int winner);
    int collCheck(int i, int j, int k);
    int colls[24] = {0,9,21,3,10,18,6,11,15,1,4,7,16,19,22,8,12,17,5,13,21,2,14,23};
};

#endif // BOARD_H
