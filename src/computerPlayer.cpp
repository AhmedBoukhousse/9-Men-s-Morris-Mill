#include "computerPlayer.h"

computerPlayer::computerPlayer()
{
  srand(time(NULL));
}

void computerPlayer::updateHumanVectors(int pos1, int pos2, Board tempBoard)
{
  if(pos2 != -1)
  {
    int millNr;
    int points [3];

    // Check if existing mill has been broken
    for(int i = 0; i <= 45; i+=3)
    {
      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      if(points[0] == pos1 || points[1] == pos1 || points[2] == pos1)
      {
        if(tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID)
          onePieceLeftHuman.push_back(i/3);
      }
    }

    for(int i = 0; i < onePieceLeftHuman.size();)
    {
      millNr = onePieceLeftHuman[i] * 3;
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2)
      {
        onePieceLeftHuman.erase(onePieceLeftHuman.begin()+i);
        twoPiecesLeftHuman.push_back(millNr);
      }
      else
        i++;
    }

    for(int i = 0; i < twoPiecesLeftHuman.size();)
    {
      millNr = twoPiecesLeftHuman[i] * 3;
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2)
        twoPiecesLeftHuman.erase(twoPiecesLeftHuman.begin()+i);
      else
        i++;
    }

    for(int i = 0; i < impossibleHuman.size();)
    {
      millNr = impossibleHuman[i] * 3;

      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      if((points[0] == pos2 || points[1] == pos2 || points[2] == pos2) && (tempBoard.boardArea[points[0]] != HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] != HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] != HUMAN_PLAYER_ID))
        impossibleHuman.erase(impossibleHuman.begin()+i);
      else
        i++;
    }

    // Check if removing this piece has made a mill that was previously impossible for the AI
    int aiPieces = 0;
    int humanPieces = 0;
    for(int i = 0; i < impossible.size();)
    {
      millNr = impossible[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      if(points[0] != pos2 && points[1] != pos2 && points[2] != pos2)
      {
        i++;
        continue;
      }

      aiPieces = 0;
      humanPieces = 0;
      for(int k = 0; k < 3; k++)
      {
        if(tempBoard.boardArea[points[k]] == HUMAN_PLAYER_ID)
          humanPieces++;
        else if(tempBoard.boardArea[points[k]] == AI_PLAYER_ID)
          aiPieces++;
      }
      // Check if the mill is now possible (no more human player pieces in the mill after removing one)
      if(humanPieces == 1)
      {
        if(aiPieces == 1)
        {
          impossible.erase(find(impossible.begin(), impossible.end(), millNr/3));
          twoPiecesLeft.push_back(millNr/3);
        }
        else if(aiPieces == 2)
        {
          impossible.erase(find(impossible.begin(), impossible.end(), millNr/3));
          onePieceLeft.push_back(millNr/3);
        }
        i++;
      }
      else
        i++;
    }
  }

  if(pos1 != -1)
  {
    for(int j = 0; j <= 45; j+=3)
    {
      if(tempBoard.mills[j] == pos1 || tempBoard.mills[j+1] == pos1 || tempBoard.mills[j+2] == pos1)
      {
        if(tempBoard.boardArea[tempBoard.mills[j]] == AI_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+1]] == AI_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+2]] == AI_PLAYER_ID)
        {
          if(find(impossibleHuman.begin(), impossibleHuman.end(), j/3) == impossibleHuman.end())
            impossibleHuman.push_back(j/3);

          if(find(onePieceLeft.begin(), onePieceLeft.end(), j/3) != onePieceLeft.end())
          {
            onePieceLeft.erase(find(onePieceLeft.begin(), onePieceLeft.end(), j/3));
            impossible.push_back(j/3);
          }
          else if(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3) != twoPiecesLeft.end())
          {
            twoPiecesLeft.erase(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3));
            impossible.push_back(j/3);
          }
        }
        else
        {
          if(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3) != onePieceLeftHuman.end())
          {
            onePieceLeftHuman.erase(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3));
          }
          else if(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3) != twoPiecesLeftHuman.end())
          {
            twoPiecesLeftHuman.erase(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3));
            onePieceLeftHuman.push_back(j/3);
          }
          else
          {
            twoPiecesLeftHuman.push_back(j/3);
          }
        }
      }
    }
  }
}

//similair functionality to updateHumanVectors
void computerPlayer::updateAIVectors(int pos1, int pos2, Board tempBoard)
{
  if(pos2 != -1)
  {
    int millNr;
    int points [3];
    for(int i = 0; i <= 45; i+=3)
    {
      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      if(points[0] == pos1 || points[1] == pos1 || points[2] == pos1)
      {
        if(tempBoard.boardArea[points[0]] == AI_PLAYER_ID && tempBoard.boardArea[points[1]] == AI_PLAYER_ID && tempBoard.boardArea[points[2]] == AI_PLAYER_ID)
          onePieceLeft.push_back(i/3);
      }
    }

    for(int i = 0; i < onePieceLeft.size();)
    {
      millNr = onePieceLeft[i] * 3;
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2)
      {
        onePieceLeft.erase(onePieceLeft.begin()+i);
        twoPiecesLeft.push_back(millNr);
      }
      else
        i++;
    }

    for(int i = 0; i < twoPiecesLeft.size();)
    {
      millNr = twoPiecesLeft[i] * 3;
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2)
      {
        twoPiecesLeft.erase(twoPiecesLeft.begin()+i);
      }
      else
        i++;
    }

    for(int i = 0; i < impossible.size();)
    {
      millNr = impossible[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      // If only pos2 was involved, remove
      if((points[0] == pos2 || points[1] == pos2 || points[2] == pos2) && (tempBoard.boardArea[points[0]] != AI_PLAYER_ID && tempBoard.boardArea[points[1]] != AI_PLAYER_ID && tempBoard.boardArea[points[2]] != AI_PLAYER_ID))
      {
        impossible.erase(impossible.begin()+i);
      }
      else
        i++;
    }

    int aiPieces = 0;
    int humanPieces = 0;
    for(int i = 0; i < impossibleHuman.size();)
    {
      millNr = impossibleHuman[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      if(points[0] != pos2 && points[1] != pos2 && points[2] != pos2)
      {
        i++;
        continue;
      }

      aiPieces = 0;
      humanPieces = 0;

      for(int k = 0; k < 3; k++)
      {
        if(tempBoard.boardArea[points[k]] == 1)
        {
          humanPieces++;
        }
        else if(tempBoard.boardArea[points[k]] == 2)
        {
          aiPieces++;
        }
      }

      if(aiPieces == 1)
      {
        if(humanPieces == 1)
        {
          impossibleHuman.erase(find(impossibleHuman.begin(), impossibleHuman.end(), millNr/3));
          twoPiecesLeftHuman.push_back(millNr/3);
        }
        else if(humanPieces == 2)
        {
          impossibleHuman.erase(find(impossibleHuman.begin(), impossibleHuman.end(), millNr/3));
          onePieceLeftHuman.push_back(millNr/3);
        }
        i++;
      }
      else
        i++;
    }
  }

  if(pos1 != -1)
  {
    for(int j = 0; j <= 45; j+=3)
    {
      if(tempBoard.mills[j] == pos1 || tempBoard.mills[j+1] == pos1 || tempBoard.mills[j+2] == pos1)
      {
        if(tempBoard.boardArea[tempBoard.mills[j]] == HUMAN_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+1]] == HUMAN_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+2]] == HUMAN_PLAYER_ID)
        {
          if(find(impossible.begin(), impossible.end(), j/3) == impossible.end())
            impossible.push_back(j/3);

          if(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3) != onePieceLeftHuman.end())
          {
            onePieceLeftHuman.erase(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3));
            impossibleHuman.push_back(j/3);
          }
          else if(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3) != twoPiecesLeftHuman.end())
          {
            twoPiecesLeftHuman.erase(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3));
            impossibleHuman.push_back(j/3);
          }
        }
        else
        {
          if(find(onePieceLeft.begin(), onePieceLeft.end(), j/3) != onePieceLeft.end())
          {
            onePieceLeft.erase(find(onePieceLeft.begin(), onePieceLeft.end(), j/3));
          }
          else if(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3) != twoPiecesLeft.end())
          {
            twoPiecesLeft.erase(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3));
            onePieceLeft.push_back(j/3);
          }
          else
            twoPiecesLeft.push_back(j/3);
        }
      }
    }
  }
}


int computerPlayer::AIPlacePiece(Board tempBoard)
{
    //form AI mill
  if(!(onePieceLeft.empty()))
  {
    int r = rand() % onePieceLeft.size();
    int millNr = onePieceLeft.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0)
          return tempBoard.mills[millNr+i];
    }
  }

  //block human mill
  if(!(onePieceLeftHuman.empty()))
  {
    int r = rand() % onePieceLeftHuman.size();
    int millNr = onePieceLeftHuman.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0)
          return tempBoard.mills[millNr+i];
    }
  }

  //start moving towrds mill
  if(!(twoPiecesLeft.empty()))
  {
    int r = rand() % twoPiecesLeft.size();
    int millNr = twoPiecesLeft.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0)
          return tempBoard.mills[millNr+i];
    }
  }

  // #4 Place at one of four center positions

  int centralPositions [4] = {7, 11, 12, 16};

  if(tempBoard.boardArea[centralPositions[0]] == 0 || tempBoard.boardArea[centralPositions[1]] == 0 || tempBoard.boardArea[centralPositions[2]] == 0)
  {
    int r;

    do
    {
      r = rand() % 3;
    } while(tempBoard.boardArea[centralPositions[r]] != 0);

    return centralPositions[r];
  }

  // blokc human starting mill

  if(!(twoPiecesLeftHuman.empty()))
  {
    int r = rand() % twoPiecesLeftHuman.size();
    int millNr = twoPiecesLeftHuman.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0)
          return tempBoard.mills[millNr+i];
    }
  }

  // place random piece

  int r;

  do
  {
    r = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[r] != 0);

  return r;
}

int computerPlayer::AIRemovePiece(Board tempBoard)
{

  int millNr;
  int points [3];

  // #1.2 Check for blocked mill
  for(int i = 0; i < impossible.size(); i++)
  {
    millNr = impossible[i] * 3;

    points[0] = tempBoard.mills[millNr];
    points[1] = tempBoard.mills[millNr+1];
    points[2] = tempBoard.mills[millNr+2];

    if(((tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID) ^ (tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID) ^ (tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID)) && !(tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID))
    {
      for(int i = 0; i < 3; i++)
      {
        if(tempBoard.boardArea[points[i]] == HUMAN_PLAYER_ID)
            return points[i];
      }
    }
  }
   int r;

  //pick random mill
  if(impossible.size() > 0)
  {
      r = rand() % impossible.size();
      millNr = impossible.at(r) * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      for(int i = 0; i < 3; i++)
      {
        if(points[i] == HUMAN_PLAYER_ID)
            return points[i];
      }
}
  // #2 Remove a opponent mill being built

  for(int i = 0; i < onePieceLeftHuman.size(); i++)
  {
    millNr = onePieceLeftHuman[i] * 3;

    points[0] = tempBoard.mills[millNr];
    points[1] = tempBoard.mills[millNr+1];
    points[2] = tempBoard.mills[millNr+2];

    for(int i = 0; i < 3; i++)
    {
      if(points[i] == HUMAN_PLAYER_ID)
          return points[i];
    }
  }

  // #3 Remove most mill related piece

  int involvedInPotentialMills [BOARD_SIZE] = {0};
  int involvedInMostPotentialMills = -1;
  for(int i = 0; i < BOARD_SIZE; i++)
  {
    if(tempBoard.boardArea[i] == HUMAN_PLAYER_ID)
    {
      for(int j = 0; j <= 45; j+=3)
      {
        if(tempBoard.mills[j] == i || tempBoard.mills[j+1] == i || tempBoard.mills[j+2] == i)
        {
          if(tempBoard.boardArea[tempBoard.mills[j]] != 2 && tempBoard.boardArea[tempBoard.mills[j+1]] != 2 && tempBoard.boardArea[tempBoard.mills[j+2]] != 2)
          {
            involvedInPotentialMills[i]++;
            if(involvedInPotentialMills[i] > involvedInPotentialMills[involvedInMostPotentialMills])
            {
              involvedInMostPotentialMills = i;
            }
          }
        }
      }
    }
  }

  if(involvedInMostPotentialMills != -1)
  {
    return involvedInMostPotentialMills;
  }

  // #4 Remove random piece
  do
  {
    r = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[r] != 1 || tempBoard.isRemovable(r) == false);

  return r;
}

pair<int,int> computerPlayer::AIMovePiece(Board tempBoard)
{
  int pos1, pos2;
  int millNr;

  //form a mill
  if(!onePieceLeft.empty())
  {
    for(int i = 0; i < onePieceLeft.size(); i++)
    {
      millNr = onePieceLeft[i] * 3;
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          pos1 = canBeReached(pos2,tempBoard);
          if(pos1 != -1)
              return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #2 Block opposing player mill

  if(!onePieceLeftHuman.empty())
  {
    for(int i = 0; i < onePieceLeftHuman.size(); i++)
    {
      millNr = onePieceLeftHuman[i];
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          pos1 = canBeReached(pos2,tempBoard);
          if(pos1 != -1)
              return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #3 Move one piece in a mill

  int points [3];

  for(int i = 0; i <= 45; i+=3)
  {
    points[0] = tempBoard.mills[i];
    points[1] = tempBoard.mills[i+1];
    points[2] = tempBoard.mills[i+2];

    if(tempBoard.boardArea[points[0]] == AI_PLAYER_ID && tempBoard.boardArea[points[1]] == AI_PLAYER_ID && tempBoard.boardArea[points[2]] == AI_PLAYER_ID)
    {
      int r = rand() % 3;
      pos1 = points[r];

      for(int j = 0; j <= 62; j+=2)
      {
        if(tempBoard.adjacent[j] == pos1)
        {
          if(tempBoard.boardArea[tempBoard.adjacent[j+1]] == 0)
          {
            pos2 = tempBoard.adjacent[j+1];
            return make_pair(pos1, pos2);
          }
        }
        else if(tempBoard.adjacent[j+1] == pos1)
        {
          if(tempBoard.boardArea[tempBoard.adjacent[j]] == 0)
          {
            pos2 = tempBoard.adjacent[j];
            return make_pair(pos1, pos2);
          }
        }
      }
    }
  }

  // #4 Move random piece

  do
  {
    pos2 = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[pos2] != 0 || canBeReached(pos2,tempBoard) == -1 || tempBoard.boardArea[canBeReached(pos2,tempBoard)] == HUMAN_PLAYER_ID);

  pos1 = canBeReached(pos2,tempBoard);

  return make_pair(pos1, pos2);
}

int computerPlayer::canBeReached(int pos2, Board moreBoard)
{
  int pos1;

  for(int i = 0; i < 64; i+=2)
  {
    if(moreBoard.adjacent[i] == pos2)
    {
      pos1 = moreBoard.adjacent[i+1];
      if(moreBoard.boardArea[pos1] == AI_PLAYER_ID)
          return pos1;
    }
    else if(moreBoard.adjacent[i+1] == pos2)
    {
      pos1 = moreBoard.adjacent[i];
      if(moreBoard.boardArea[pos1] == AI_PLAYER_ID)
          return pos1;
    }
  }
  return -1;
}

pair<int,int> computerPlayer::AIFlyPiece(Board tempBoard)
{
  int pos1, pos2;

  vector<int> piecesOnBoard;
  for(int i = 0; i < BOARD_SIZE; i++)
  {
      if (tempBoard.boardArea[i] == AI_PLAYER_ID)
          piecesOnBoard.push_back(i);
  }

  int millNr;

  //Form mill
  if(!onePieceLeft.empty())
  {
    for(int i = 0; i < onePieceLeft.size(); i++)
    {
      millNr = onePieceLeft[i];
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  //Block opposing mill
  if(!onePieceLeftHuman.empty())
  {
    for(int i = 0; i < onePieceLeftHuman.size(); i++)
    {
      millNr = onePieceLeftHuman[i];
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  //Start forming mill

  if(!twoPiecesLeft.empty())
  {
    for(int i = 0; i < twoPiecesLeft.size(); i++)
    {
      millNr = twoPiecesLeft[i];
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #4 block  player's eventual mill

  if(!twoPiecesLeftHuman.empty())
  {
    for(int i = 0; i < twoPiecesLeftHuman.size(); i++)
    {
      millNr = twoPiecesLeftHuman[i];
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  //Move random piece
  int randomPosition1 = rand() % piecesOnBoard.size();
  pos1 = piecesOnBoard.at(randomPosition1);

  do
  {
    pos2 = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[pos2] != 0);

  return make_pair(pos1, pos2);
}
