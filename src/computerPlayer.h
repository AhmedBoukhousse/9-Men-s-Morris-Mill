#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <vector>
#include <ctime>
#include <array>
#include "board.h"

using namespace std;

#define HUMAN_PLAYER_ID 1
#define AI_PLAYER_ID 2
#define BOARD_SIZE 24

class computerPlayer
{
  public:

    //constrcutor
    computerPlayer();

    //AI Vector functions
    void updateHumanVectors(int pos1, int pos2, Board tempBoard);
    void updateAIVectors(int pos1, int pos2, Board tempBoard);

    //AI Functions
    int AIPlacePiece(Board tempBoard);
    int AIRemovePiece(Board tempBoard);
    pair<int,int> AIMovePiece(Board tempBoard);
    pair<int,int> AIFlyPiece(Board tempBoard);

    //Adjacency Function
    int canBeReached(int pos2, Board moreBoard);

  private:
    vector<int> onePieceLeft, twoPiecesLeft, impossible, onePieceLeftHuman, twoPiecesLeftHuman, impossibleHuman;
};

#endif // COMPUTERPLAYER_H
