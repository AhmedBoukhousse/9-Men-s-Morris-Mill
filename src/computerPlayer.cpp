#include "computerPlayer.h"

computerPlayer::computerPlayer()
{
  srand(time(NULL));
}

void computerPlayer::updateHumanVectors(int pos1, int pos2, Board tempBoard)
{
  // pos1: Position of the human player's piece that was just placed
  // pos2: Position of the human player's piece that was just removed

  // Case 1: Human player has just placed a piece
  // => pos1 is set, pos2 is -1

  // Case 2: Human player has just moved a piece
  // => pos1 and pos2 are set

  // Case 3: AI player has just removed one of the human player's pieces
  // => pos2 is set, pos1 is -1

  // If pos2 is set
  // Check if existing or possible mills have been broken
  // Should be done first in case the removed piece is involved in a possible mill with the added piece
  if(pos2 != -1)
  {
    int millNr;
    int points [3];

    // Check if existing mill has been broken
    for(int i = 0; i <= 45; i+=3)
    {
      // Save the three points of the mill as points 1-3
      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      // Go through all possible mill positions involving the piece that is being moved
      if(points[0] == pos1 || points[1] == pos1 || points[2] == pos1)
      {
        // Check if the mill involving the moved piece was previously formed
        if(tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID)
        {
          // If yes, add the mill nr to onePieceLeftHuman
          onePieceLeftHuman.push_back(i/3);
        }
      }
    }

    // Go through onePieceLeftHuman
    for(int i = 0; i < onePieceLeftHuman.size();)
    {
      millNr = onePieceLeftHuman[i] * 3;

      // If pos2 was involved, move to twoPiecesLeftHuman
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2) {
        onePieceLeftHuman.erase(onePieceLeftHuman.begin()+i);
        twoPiecesLeftHuman.push_back(millNr);
      } else {
        i++;
      }
    }

    // Go through twoPiecesLeftHuman and impossibleHuman
    for(int i = 0; i < twoPiecesLeftHuman.size();)
    {
      millNr = twoPiecesLeftHuman[i] * 3;

      // If pos2 was involved, remove
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2) {
        twoPiecesLeftHuman.erase(twoPiecesLeftHuman.begin()+i);
      } else {
        i++;
      }
    }

    for(int i = 0; i < impossibleHuman.size();)
    {
      millNr = impossibleHuman[i] * 3;

      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      // If only pos2 was involved, remove
      if((points[0] == pos2 || points[1] == pos2 || points[2] == pos2) && (tempBoard.boardArea[points[0]] != HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] != HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] != HUMAN_PLAYER_ID)) {
        impossibleHuman.erase(impossibleHuman.begin()+i);
      } else {
        i++;
      }
    }

    // Check if removing this piece has made a mill that was previously impossible for the AI player possible (May cause issues)
    int aiPieces = 0;
    int humanPieces = 0;
    for(int i = 0; i < impossible.size();)
    {
      millNr = impossible[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      // Check if mill involves the removed piece
      if(points[0] != pos2 && points[1] != pos2 && points[2] != pos2)
      {
        i++;
        continue;
      }
      // Count pieces in the mill placed by the human and the AI player

      aiPieces = 0;
      humanPieces = 0;
      for(int k = 0; k < 3; k++)
      {
        if(tempBoard.boardArea[points[k]] == HUMAN_PLAYER_ID)
        {
          humanPieces++;
        }
        else if(tempBoard.boardArea[points[k]] == AI_PLAYER_ID)
        {
          aiPieces++;
        }
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
      }
      i++;
    }
  }

  // If pos1 is set
  // Check if there are new possible mills
  if(pos1 != -1)
  {
    for(int j = 0; j <= 45; j+=3)
    {
      // Go through all possible mill positions involving the piece that was just placed
      if(tempBoard.mills[j] == pos1 || tempBoard.mills[j+1] == pos1 || tempBoard.mills[j+2] == pos1)
      {
        if(tempBoard.boardArea[tempBoard.mills[j]] == AI_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+1]] == AI_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+2]] == AI_PLAYER_ID)
        {
          if(find(impossibleHuman.begin(), impossibleHuman.end(), j/3) == impossibleHuman.end())
          {
            impossibleHuman.push_back(j/3);
          }

          // Check if placing this piece has made a mill that was previously possible for the AI player impossible
          if(find(onePieceLeft.begin(), onePieceLeft.end(), j/3) != onePieceLeft.end()) {
            onePieceLeft.erase(find(onePieceLeft.begin(), onePieceLeft.end(), j/3));
            impossible.push_back(j/3);
          } else if(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3) != twoPiecesLeft.end()) {
            twoPiecesLeft.erase(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3));
            impossible.push_back(j/3);
          }

        }
        else
        {
          if(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3) != onePieceLeftHuman.end())
          {
            // If j already is in onePieceLeft, it is already a completed mill, do nothing, just erase
            onePieceLeftHuman.erase(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3));
          }
          else if(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3) != twoPiecesLeftHuman.end())
          {
            // If j already is in twoPiecesLeft, move to onePieceLeft
            twoPiecesLeftHuman.erase(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3));
            onePieceLeftHuman.push_back(j/3);
          }
          else
          {
            // If j isn't already in onePieceLeft or twoPiecesLeft, add to twoPiecesLeft
            twoPiecesLeftHuman.push_back(j/3);
          }
        }
      }
    }
  }
}

void computerPlayer::updateAIVectors(int pos1, int pos2, Board tempBoard)
{
  // pos1: Position of the AI player's piece that was just placed
  // pos2: Position of the AI player's piece that was just removed

  // Case 1: AI player has just placed a piece
  // => pos1 is set, pos2 is -1

  // Case 2: AI player has just moved a piece
  // => pos1 and pos2 are set

  // Case 3: Human player has just removed one of the AI player's pieces
  // => pos2 is set, pos1 is -1

  // If pos2 is set
  // Check if existing or possible mills have been broken
  // Should be done first in case the removed piece is involved in a possible mill with the added piece
  if(pos2 != -1)
  {
    int millNr;
    int points [3];

    // Check if existing mill has been broken
    for(int i = 0; i <= 45; i+=3)
    {
      // Save the three points of the mill as points 1-3
      points[0] = tempBoard.mills[i];
      points[1] = tempBoard.mills[i+1];
      points[2] = tempBoard.mills[i+2];

      // Go through all possible mill positions involving the piece that is being moved
      if(points[0] == pos1 || points[1] == pos1 || points[2] == pos1)
      {
        // Check if the mill involving the moved piece was previously formed
        if(tempBoard.boardArea[points[0]] == AI_PLAYER_ID && tempBoard.boardArea[points[1]] == AI_PLAYER_ID && tempBoard.boardArea[points[2]] == AI_PLAYER_ID)
        {
          // If yes, add the mill nr to onePieceLeft
          onePieceLeft.push_back(i/3);
        }
      }
    }

    // Go through onePieceLeft
    for(int i = 0; i < onePieceLeft.size();)
    {
      millNr = onePieceLeft[i] * 3;

      // If pos2 was involved, move to twoPiecesLeft
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2) {
        onePieceLeft.erase(onePieceLeft.begin()+i);
        twoPiecesLeft.push_back(millNr);
      } else {
        i++;
      }
    }

    // Go through twoPiecesLeft and impossible
    for(int i = 0; i < twoPiecesLeft.size();)
    {
      millNr = twoPiecesLeft[i] * 3;

      // If pos2 was involved, remove
      if(tempBoard.mills[millNr] == pos2 || tempBoard.mills[millNr+1] == pos2 || tempBoard.mills[millNr+2] == pos2) {
        twoPiecesLeft.erase(twoPiecesLeft.begin()+i);
      } else {
        i++;
      }
    }

    for(int i = 0; i < impossible.size();)
    {
      millNr = impossible[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      // If only pos2 was involved, remove
      if((points[0] == pos2 || points[1] == pos2 || points[2] == pos2) && (tempBoard.boardArea[points[0]] != AI_PLAYER_ID && tempBoard.boardArea[points[1]] != AI_PLAYER_ID && tempBoard.boardArea[points[2]] != AI_PLAYER_ID)) {
        impossible.erase(impossible.begin()+i);
      } else {
        i++;
      }
    }

    // Check if removing this piece has made a mill that was previously impossible for the human player possible (This one may cause issues)
    int aiPieces = 0;
    int humanPieces = 0;
    for(int i = 0; i < impossibleHuman.size();)
    {
      millNr = impossibleHuman[i] * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      // Check if mill involves the removed piece

      if(points[0] != pos2 && points[1] != pos2 && points[2] != pos2)
      {
        i++;
        continue;
      }

      // Count pieces in the mill placed by the human and the AI player

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
      // Check if the mill is now possible (no more AI player pieces in the mill after removing one)
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
      }
      i++;
    }
  }

  // If pos1 is set
  // Check if there are new possible mills
  if(pos1 != -1)
  {
    for(int j = 0; j <= 45; j+=3)
    {
      // Go through all possible mill positions involving the piece that was just placed
      if(tempBoard.mills[j] == pos1 || tempBoard.mills[j+1] == pos1 || tempBoard.mills[j+2] == pos1)
      {
        if(tempBoard.boardArea[tempBoard.mills[j]] == HUMAN_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+1]] == HUMAN_PLAYER_ID || tempBoard.boardArea[tempBoard.mills[j+2]] == HUMAN_PLAYER_ID)
        {
          if(find(impossible.begin(), impossible.end(), j/3) == impossible.end())
          {
            impossible.push_back(j/3);
          }

          // Check if placing this piece has made a mill that was previously possible for the human player impossible
          if(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3) != onePieceLeftHuman.end()) {
            onePieceLeftHuman.erase(find(onePieceLeftHuman.begin(), onePieceLeftHuman.end(), j/3));
            impossibleHuman.push_back(j/3);
          } else if(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3) != twoPiecesLeftHuman.end()) {
            twoPiecesLeftHuman.erase(find(twoPiecesLeftHuman.begin(), twoPiecesLeftHuman.end(), j/3));
            impossibleHuman.push_back(j/3);
          }

        }
        else
        {
          if(find(onePieceLeft.begin(), onePieceLeft.end(), j/3) != onePieceLeft.end())
          {
            // If j already is in onePieceLeft, it is now a completed mill, do nothing, just erase
            onePieceLeft.erase(find(onePieceLeft.begin(), onePieceLeft.end(), j/3));
          }
          else if(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3) != twoPiecesLeft.end())
          {
            // If j already is in twoPiecesLeft, move to onePieceLeft
            twoPiecesLeft.erase(find(twoPiecesLeft.begin(), twoPiecesLeft.end(), j/3));
            onePieceLeft.push_back(j/3);
          }
          else
          {
            // If j isn't already in onePieceLeft or twoPiecesLeft, add to twoPiecesLeft
            twoPiecesLeft.push_back(j/3);
          }
        }
      }
    }
  }
}


int computerPlayer::AIPlacePiece(Board tempBoard)
{
  // The AI's priorities are:
  // #1 Form a mill when one piece is left
  // #2 Block a mill of the opposing player when one piece is left
  // #3 Start forming a mill when two pieces are left
  // #4 Place at one of the central four positions (7, 11, 12, 16)
  // #5 Block a mill of the opposing player when two pieces are left
  // #6 Place at a random position

  // STEPS

  // #1 Form a mill when one piece is left
  // #1.1 If onePieceLeft isn't empty, pick a random mill out of the vector and form it

  if(!(onePieceLeft.empty()))
  {
    int r = rand() % onePieceLeft.size();
    int millNr = onePieceLeft.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0) return tempBoard.mills[millNr+i];
    }
  }

  // #2 Block a mill of the opposing player when one piece is left
  // #2.1 If onePieceLeftHuman isn't empty, pick a random mill out of the vector and block it

  if(!(onePieceLeftHuman.empty()))
  {
    int r = rand() % onePieceLeftHuman.size();
    int millNr = onePieceLeftHuman.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0) return tempBoard.mills[millNr+i];
    }
  }

  // #3 Start forming a mill when two pieces are left
  // #3.1 If twoPiecesLeft isn't empty, pick a random mill out of the vector and start forming it

  if(!(twoPiecesLeft.empty()))
  {
    int r = rand() % twoPiecesLeft.size();
    int millNr = twoPiecesLeft.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0) return tempBoard.mills[millNr+i];
    }
  }

  // #4 Place at one of the central four positions (7, 11, 12, 16)

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

  // #5 Block a mill of the opposing player when two pieces are left
  // #5.1 If onePieceLeftHuman isn't empty, pick a random mill out of the vector and block it

  if(!(twoPiecesLeftHuman.empty()))
  {
    int r = rand() % twoPiecesLeftHuman.size();
    int millNr = twoPiecesLeftHuman.at(r) * 3;
    for(int i = 0; i < 3; i++)
    {
      if(tempBoard.boardArea[tempBoard.mills[millNr+i]] == 0) return tempBoard.mills[millNr+i];
    }
  }

  // #6 Place at a random position

  int r;

  do
  {
    r = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[r] != 0);

  return r;
}

int computerPlayer::AIRemovePiece(Board tempBoard)
{
  // The AI's priorities are:
  // #1 Free a blocked mill
  // #2 Remove a piece of the opposing player in a mill with one piece left
  // #3 Remove the piece of the opposing player that is involved in the most possible mills
  // #4 Remove a random piece

  // STEPS

  // #1 Free a blocked mill
  // #1.1 Go through the impossible vector (contains all impossible mills that are blocked in some way)

  int millNr;
  int points [3];

  // #1.2 Check if there is a mill that is only blocked a single piece
  for(int i = 0; i < impossible.size(); i++)
  {
    millNr = impossible[i] * 3;

    points[0] = tempBoard.mills[millNr];
    points[1] = tempBoard.mills[millNr+1];
    points[2] = tempBoard.mills[millNr+2];

    // Uses XOR: (a ^ b ^ c) && !(a && b && c)
    if(((tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID) ^ (tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID) ^ (tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID)) && !(tempBoard.boardArea[points[0]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[1]] == HUMAN_PLAYER_ID && tempBoard.boardArea[points[2]] == HUMAN_PLAYER_ID))
    {
      for(int i = 0; i < 3; i++)
      {
        // and return the position of the blocking piece
        if(tempBoard.boardArea[points[i]] == HUMAN_PLAYER_ID) return points[i];
      }
    }
  }
   int r;
  // #1.3 Else pick a random mill
  if(impossible.size() > 0) {
      r = rand() % impossible.size();
      millNr = impossible.at(r) * 3;

      points[0] = tempBoard.mills[millNr];
      points[1] = tempBoard.mills[millNr+1];
      points[2] = tempBoard.mills[millNr+2];

      for(int i = 0; i < 3; i++)
      {
        // and return the position of the blocking piece
        if(points[i] == HUMAN_PLAYER_ID) return points[i];
      }
}
  // #2 Remove a piece of the opposing player in a mill with one piece left

  for(int i = 0; i < onePieceLeftHuman.size(); i++)
  {
    millNr = onePieceLeftHuman[i] * 3;

    points[0] = tempBoard.mills[millNr];
    points[1] = tempBoard.mills[millNr+1];
    points[2] = tempBoard.mills[millNr+2];

    for(int i = 0; i < 3; i++)
    {
      if(points[i] == HUMAN_PLAYER_ID) return points[i];
    }
  }

  // #3 Remove the piece of the opposing player that is involved in the most possible mills

  int involvedInPotentialMills [BOARD_SIZE] = {0};
  int involvedInMostPotentialMills = -1;

  // #3.1 Go through all vertices == HUMAN_PLAYER_ID
  // and check if they are part of a possible mill; if yes, increase count involvedInPotentialMills
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
            // Piece i is involved in a possible Muehle
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

  // #3.2 If it exists, return the one that is part of the most possible mills

  if(involvedInMostPotentialMills != -1)
  {
    return involvedInMostPotentialMills;
  }

  // #4 Remove a random piece

  do
  {
    r = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[r] != 1 || tempBoard.isRemovable(r) == true);

  return r;
}

pair<int,int> computerPlayer::AIMovePiece(Board tempBoard)
{
  int pos1, pos2;

  // The AI's priorities are:
  // #1 Form a mill when onePieceLeft and canBeReached
  // #2 Block a mill of the opposing player when onePieceLeft and canBeReached
  // #3 Move one piece in a mill
  // #4 Move a random piece

  // STEPS

  // #1 Form a mill when onePieceLeft and canBeReached
  // #1.1 Check if onePieceLeft is not empty and canBeReached

  int millNr;

  if(!onePieceLeft.empty())
  {
    for(int i = 0; i < onePieceLeft.size(); i++)
    {
      // Get number of the mill
      millNr = onePieceLeft[i] * 3;
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Check if the empty position can be reached
          // canBeReached returns position from where pos2 can be reached if it exists, otherwise it returns -1
          pos1 = canBeReached(pos2,tempBoard);
          if(pos1 != -1) return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #2 Block a mill of the opposing player when onePieceLeft and canBeReached
  // #2.1 Check if onePieceLeftHuman is not empty and canBeReached

  if(!onePieceLeftHuman.empty())
  {
    for(int i = 0; i < onePieceLeftHuman.size(); i++)
    {
      // Get number of the mill
      millNr = onePieceLeftHuman[i];
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Check if the empty position can be reached
          // canBeReached returns position from where pos2 can be reached if it exists, otherwise it returns -1
          pos1 = canBeReached(pos2,tempBoard);
          if(pos1 != -1) return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #3 Move one piece in a mill

  // #3.1 Find formed mills

  int points [3];

  for(int i = 0; i <= 45; i+=3)
  {
    // Save the three points of the mill as point1-3
    points[0] = tempBoard.mills[i];
    points[1] = tempBoard.mills[i+1];
    points[2] = tempBoard.mills[i+2];

    // Check if the mill is formed
    if(tempBoard.boardArea[points[0]] == AI_PLAYER_ID && tempBoard.boardArea[points[1]] == AI_PLAYER_ID && tempBoard.boardArea[points[2]] == AI_PLAYER_ID)
    {
      // #3.2 If yes, move a piece at a random position of the mill
      int r = rand() % 3;
      pos1 = points[r];

      // #3.3 Find a empty position that is connected to that position

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
          if(tempBoard.boardArea[tempBoard.adjacent[j]] == 0) {
            pos2 = tempBoard.adjacent[j];
            return make_pair(pos1, pos2);
          }
        }
      }
    }
  }

  // #4 Move a random piece

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
  // #1 Go through all edges
  for(int i = 0; i <= 62; i+=2)
  {
    // #2 Check if they involve positon pos2
    if(moreBoard.adjacent[i] == pos2)
    {
      pos1 = moreBoard.adjacent[i+1];
      // #3 Check if they also involve a position where the AI player has placed a piece
      // If yes, return that position
      if(moreBoard.boardArea[pos1] == AI_PLAYER_ID) return pos1;
    }
    // #2 Check if they involve positon pos2
    else if(moreBoard.adjacent[i+1] == pos2)
    {
      pos1 = moreBoard.adjacent[i];
      // #3 Check if they also involve a position where the AI player has placed a piece
      // If yes, return that position
      if(moreBoard.boardArea[pos1] == AI_PLAYER_ID) return pos1;
    }
  }

  // #4 If none are, return -1
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

  // The AI's priorities are:
  // #1 Form a mill when onePieceLeft
  // #2 Block a mill of the opposing player when onePieceLeft
  // #3 Start forming a mill when twoPiecesLeft
  // #4 Block a mill of the opposing player when twoPiecesLeft

  // STEPS

  // #1 Form a mill when onePieceLeft
  // #1.1 Check if onePieceLeft is not empty

  int millNr;

  if(!onePieceLeft.empty())
  {
    for(int i = 0; i < onePieceLeft.size(); i++)
    {
      // Get number of the mill
      millNr = onePieceLeft[i];
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        // pos2 is the empty position of the mill
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Return position of random AI player's piece
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #2 Block a mill of the opposing player when onePieceLeft
  // #2.1 Check if onePieceLeftHuman is not empty

  if(!onePieceLeftHuman.empty())
  {
    for(int i = 0; i < onePieceLeftHuman.size(); i++)
    {
      // Get number of the mill
      millNr = onePieceLeftHuman[i];
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        // pos2 is the empty position of the mill
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Return position of random AI player's piece
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #3 Start forming a mill when twoPiecesLeft
  // #3.1 Check if twoPiecesLeft is not empty

  if(!twoPiecesLeft.empty())
  {
    for(int i = 0; i < twoPiecesLeft.size(); i++)
    {
      // Get number of the mill
      millNr = twoPiecesLeft[i];
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        // pos2 is the first empty position of the mill
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Return position of random AI player's piece
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #4 Block a mill of the opposing player when twoPiecesLeft
  // #4.1 Check if twoPiecesLeftHuman is not empty

  if(!twoPiecesLeftHuman.empty())
  {
    for(int i = 0; i < twoPiecesLeftHuman.size(); i++)
    {
      // Get number of the mill
      millNr = twoPiecesLeftHuman[i];
      // Go through all three piece positions of the mill to figure out which one is empty
      for(int j = 0; j < 3; j++)
      {
        // pos2 is the first empty position of the mill
        pos2 = tempBoard.mills[millNr+j];
        if(tempBoard.boardArea[pos2] == 0)
        {
          // Return position of random AI player's piece
          int randomPosition = rand() % piecesOnBoard.size();
          pos1 = piecesOnBoard.at(randomPosition);
          return make_pair(pos1, pos2);
        }
      }
    }
  }

  // #5 Move random piece

  int randomPosition1 = rand() % piecesOnBoard.size();
  pos1 = piecesOnBoard.at(randomPosition1);

  do
  {
    pos2 = rand() % BOARD_SIZE;
  } while(tempBoard.boardArea[pos2] != 0);

  return make_pair(pos1, pos2);
}
