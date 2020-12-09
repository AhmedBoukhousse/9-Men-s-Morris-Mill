#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define MORRIS_AMT 9 //amount of pieces a player has
#define RED_ID 1 //ID of the Red piece
#define BLACK_ID 2 //ID of the Black piece
#define EMPTY_ID 0 //ID of an empty spot
#define BOARD_SIZE 24 //amount of spaces on the board

class Board
{
public:

    //constructors
    Board();
    Board(int area[BOARD_SIZE]); //pass predefined board area to new board object

    int boardArea[BOARD_SIZE]; //array that stores the player pieces on the board
    bool flightMode = false; //determines whether or not the player can fly
    map<int, int> playerPiecesAmt; //tracks the amount of pieces a player has left

    int checkMill(int pos); //checks if a mill was created at a certain position and who formed it
    bool checkAdjacent(int origin, int dest); //checks if one location is adjacent to another
    void addPiece(int pid, int slot); //adds a piece of a certain player to a certain location on the board
    bool allPiecesInMills(int piece); //checks if every piece a player has on the board is in a mill
    void removePiece(int slot); //removes a piece of a certain player from a certain location on the board
    void movePiece(int pid, int origin, int dest); //moves a piece from one location on the board to another
    bool hasLegalMoves(int pid); //checks to see if a player has any means of making a legal mvoe on the board
    bool isRemovable(int piece); //checks to see if a selected piece can be removed
    int GameOver(); //returns an integer of each scenario where a game over could occur

    //manual list of all possible mills
    int mills[48] = {0,9,21,
                     3,10,18,
                     6,11,15,
                     1,4,7,
                     16,19,22,
                     8,12,17,
                     5,13,20,
                     2,14,23,
                     0,1,2,
                     3,4,5,
                     6,7,8,
                     9,10,11,
                     12,13,14,
                     15,16,17,
                     18,19,20,
                     21,22,23};

    //manual list of all adjacent spots in a mill
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
