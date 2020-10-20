#include "board.h"
Board::Board()
{
    for(int i =0; i < 24; i++)
        boardArea[i] = 0;
    playerPieces[1] = 0; //temporary
    playerPieces[2] = 0;
}

int Board::checkMill()
{
    int p1row = 0;
    int p2row = 0;
    int collCall;
    //check rows
    for (int i = 0; i<24; i++)
    {
        //used for going to next row
        if(i == 0 || (((i+1) % 3 == 1) && ((i+1) != 2)))
        {
            p1row = 0;
            p2row = 0;
        }

        if (boardArea[i] == 0)
        {
             p1row = 0;
             p2row = 0;
        }
        else if (boardArea[i] == 1)
        {
            p1row++;
            p2row = 0;
        }
        else if (boardArea[i] == 2)
        {
            p1row = 0;
            p2row++;
        }

        //return winner
        if (p1row == 3)
            return 1;
        if (p2row == 3)
            return 2;
    }

    //check columns
        for (int i = 0; i<21; i+=3)
        {
           collCall = collCheck(colls[i],colls[i+1],colls[i+2]);

           if (collCall == 1)
               return 1;
           else if (collCall == 2)
               return 2;
        }

    //no mills means no winner
    return 0;
}

//manually check for column based mills
int Board::collCheck(int i, int j, int k)
{
    if(boardArea[i] == 1 && boardArea[j] == 1 && boardArea[k] == 1)
        return 1;
    else if (boardArea[i] == 2 && boardArea[j] == 2 && boardArea[k] == 2)
        return 2;
    else
        return 0;
}

void Board::addPiece(int pid, int slot)
{
    if(boardArea[slot] == 0 && playerPieces[pid] < 9)
    {
        boardArea[slot] =  pid;
        playerPieces[pid]++;
    }
    else
        return;
}

void Board::removePiece(int slot)
{
    if (playerPieces[boardArea[slot]] > 0) {
    int pid = boardArea[slot];
    boardArea[slot] = 0;
    playerPieces[pid] = playerPieces[pid] -  1;
    }
}

bool Board::checkAdjacent(int origin, int dest)
{
      for(int i = 0; i < 64; i+=2)
      {
        if((adjacent[i] == origin && adjacent[i+1] == dest)  || (adjacent[i] == dest && adjacent[i+1] == origin))
          return true;
      }
      return false;
}

void Board::swapPiece(int pid, int origin, int dest)
{
    if(boardArea[origin] == pid && boardArea[dest]==0)
    {
        bool adjacent = true;
        if (flightMode == false)
            adjacent = checkAdjacent(origin, dest);
        if (adjacent == true)
        {
            boardArea[origin] = 0;
            boardArea[dest] = pid;
        }
    }
}
