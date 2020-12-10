#include "board.h"

Board::Board()
{
    for(int i =0; i < BOARD_SIZE; i++) //generate empty board
        boardArea[i] = 0;
    playerPiecesAmt[RED_ID] = 0;
    playerPiecesAmt[BLACK_ID] = 0;
}

Board::Board(int area[BOARD_SIZE])
{
    for(int i =0; i < BOARD_SIZE; i++) //fill in board array with passed array
        boardArea[i] = area[i];
    playerPiecesAmt[1] = 0;
    playerPiecesAmt[2] = 0;
}

int Board::checkMill(int pos)
{
    int playerMilled = 0;
    int pos1;
    int pos2;
    int pos3;

    if(boardArea[pos] == 0)
        return 0;

    for(int i = 0; i <= 45; i+=3) //for every mill listed in the mill array
    {
        pos1 = mills[i];
        pos2 = mills[i+1];
        pos3 = mills[i+2];
        if (pos1 == pos || pos2 == pos || pos3 == pos) //check if passed piece is listed in mill array
        {
            if(boardArea[pos1] != 0 && boardArea[pos1] == boardArea[pos2] && boardArea[pos2] == boardArea[pos3]) //check if the other parts of the listed mill have the same player's pieces
                  {
                    playerMilled = boardArea[pos1]; //return the player that created the mill
                    return playerMilled;
                  }
        }
        if ((i+2) == 48)
            return 0;
    }
    return 0;
}

void Board::addPiece(int pid, int slot)
{
    if(boardArea[slot] == 0 && playerPiecesAmt[pid] < MORRIS_AMT) //check if all 9 pieces are on the boar dalready, otherwise stop
    {
        boardArea[slot] =  pid; //add the piece
        playerPiecesAmt[pid]++; //iterate on the number of pieces the player has on the board
    }
    else
        return;
}

bool Board::isRemovable(int piece)
{
    int playerOfPiece = boardArea[piece];
    if (allPiecesInMills(piece) == true) //if every piece of a player is in a mill, thyen it is removable
        return true;
    if (checkMill(piece) == playerOfPiece) //otherwise see if that piece is in a mill
        return false;
    else                                    //pieces not in mills are removable
        return true;
}

bool Board::allPiecesInMills(int piece)
{
    vector<int> milledPiecesP1;
    vector<int> milledPiecesP2;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (boardArea[i] > 0 && checkMill(i) == 1)
                milledPiecesP1.push_back(i);            //if a piece is in a mill, add it to this vector
            if (boardArea[i] > 0 && checkMill(i) == 2)
                milledPiecesP2.push_back(i);
        }
        if (milledPiecesP1.size() == playerPiecesAmt[RED_ID] && piece == RED_ID) //check if all Red pieces are in an array and if the piece selected is Red
            return true;
        else if (milledPiecesP2.size() == playerPiecesAmt[BLACK_ID] && piece == BLACK_ID) //check if all Black pieces are in an array and if the piece selected is Black
            return true;
        else
            return false;
}

int Board::GameOver()
{
    if (hasLegalMoves(1) == false && playerPiecesAmt[RED_ID] > 0) //red has no legal moves left
        return 1;
    else if (hasLegalMoves(2) == false && playerPiecesAmt[BLACK_ID] > 0) //black has no legal moves left
        return 2;
    if (playerPiecesAmt[RED_ID] < 3) //red has too little pices
        return 3;
    else if (playerPiecesAmt[BLACK_ID] < 3) //black has too little pices
        return 4;
    else
        return 5; //return value if game is not over
}

void Board::removePiece(int slot)
{
    int playerPos = boardArea[slot];
    if (playerPiecesAmt[boardArea[slot]] > 0 && (checkMill(slot) == 0 || playerPiecesAmt[playerPos] == 3 || allPiecesInMills(boardArea[slot]))) //if piece is not in a mill or is player can fly or id every other piece is in a mill
    {
        int pid = boardArea[slot];
        boardArea[slot] = 0; //set spot to empty
        playerPiecesAmt[pid] = playerPiecesAmt[pid] - 1; //subtract pieces left on board
    }
}

bool Board::checkAdjacent(int origin, int dest)
{
      for(int i = 0; i < 64; i+=2)
      {
        if((adjacent[i] == origin && adjacent[i+1] == dest)  || (adjacent[i] == dest && adjacent[i+1] == origin)) //check against adjacency array and see if 2 passed points match
          return true;
      }
      return false;
}

bool Board::hasLegalMoves(int pid)
{
    if(playerPiecesAmt[pid] == 3)
        return true;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if (boardArea[i] == pid)
        {
            for(int j = 0; j < BOARD_SIZE; j++) //see if ther are any adjacent matches against player
            {
                if (boardArea[j] == 0)
                {
                    if (checkAdjacent(i, j))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Board::movePiece(int pid, int origin, int dest)
{
    if(boardArea[origin] == pid && boardArea[dest]==0) //check if dest is empty
    {
        if (playerPiecesAmt[pid] == 3) //check if player can fly
                flightMode = true;
        bool adjacent = true;
        if (flightMode == false) //check adjacency if player can't fly
            adjacent = checkAdjacent(origin, dest);
        if (adjacent == true)
        {
            boardArea[origin] = 0; //set origin to empty
            boardArea[dest] = pid; //set dest to player
        }
    }
    flightMode = false;
}
