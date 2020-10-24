#include "board.h"
Board::Board()
{
    for(int i =0; i < 24; i++)
        boardArea[i] = 0;
    playerPieces[1] = 0; //temporary
    playerPieces[2] = 0;
}

int Board::checkMill(int pos)
{
    int playerMilled;
    int pos1;
    int pos2;
    int pos3;
    for(int i = 0; i <= 45; i+=3)
    {
        pos1 = mills[i];
        pos2 = mills[i+1];
        pos3 = mills[i+2];
        if (pos1 == pos || pos2 == pos || pos3 == pos)
        {
            if(boardArea[pos1] != 0 && boardArea[pos1] == boardArea[pos2] && boardArea[pos2] == boardArea[pos3])
                  {
                    playerMilled = boardArea[pos1];
                    return playerMilled;
                  }
        }
    }
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
    if (playerPieces[boardArea[slot]] > 0)
    {
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
