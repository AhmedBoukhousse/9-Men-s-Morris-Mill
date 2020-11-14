#include "board.h"

Board::Board()
{
    for(int i =0; i < 24; i++)
        boardArea[i] = 0;
    playerPiecesAmt[1] = 0;
    playerPiecesAmt[2] = 0;
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

void Board::addPiece(int pid, int slot)
{
    if(boardArea[slot] == 0 && playerPiecesAmt[pid] < 9)
    {
        boardArea[slot] =  pid;
        playerPiecesAmt[pid]++;
    }
    else
        return;
}

bool Board::allInMills(int piece)
{
    vector<int> milledPiecesP1;
    vector<int> milledPiecesP2;
        for (int i = 0; i < 24; i++) {
            if (boardArea[i] > 0 && checkMill(i) == 1)
                milledPiecesP1.push_back(i);
            if (boardArea[i] > 0 && checkMill(i) == 2)
                milledPiecesP2.push_back(i);
        }
        if (milledPiecesP1.size() == playerPiecesAmt[1] && piece == 1)
            return true;
        else if (milledPiecesP2.size() == playerPiecesAmt[2] && piece == 2)
            return true;
        else
            return false;
}
int Board::GameOver()
{
    if (hasLegalMoves(1) == false && playerPiecesAmt[1] > 0)
        return 1;
    else if (hasLegalMoves(2) == false && playerPiecesAmt[2] > 0)
        return 2;
    if (playerPiecesAmt[1] < 3)
        return 3;
    else if (playerPiecesAmt[2] < 3)
        return 4;
    else
        return 5;
}

void Board::removePiece(int slot)
{
    int playerPos = boardArea[slot];
    if (playerPiecesAmt[boardArea[slot]] > 0 && (checkMill(slot) == 0 || playerPiecesAmt[playerPos] == 3 || allInMills(boardArea[slot])))
    {
        int pid = boardArea[slot];
        boardArea[slot] = 0;
        playerPiecesAmt[pid] = playerPiecesAmt[pid] -  1;
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

bool Board::hasLegalMoves(int pid)
{
    for(int i = 0; i < 24; i++)
    {
        if (boardArea[i] == pid)
        {
            for(int j = 0; j < 24; j++)
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

void Board::swapPiece(int pid, int origin, int dest)
{
    if(boardArea[origin] == pid && boardArea[dest]==0)
    {
        if (playerPiecesAmt[pid] == 3)
                flightMode = true;
        bool adjacent = true;
        if (flightMode == false)
            adjacent = checkAdjacent(origin, dest);
        if (adjacent == true)
        {
            boardArea[origin] = 0;
            boardArea[dest] = pid;
        }
    }
    flightMode = false;
}
