#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <ctime>
#include <array>
#include "board.h"

using namespace std;

// Define player ID of the computer, default is 2
#define HUMAN_PLAYER_ID 1
#define AI_PLAYER_ID 2

class Move
{
  public:
    // Constructors
    Move();

    // Getters
    int getID();

    /*!
     *  Updates the onePieceLeft/onePieceLeftHuman, twoPiecesLeft/twoPiecesLeftHuman and impossible/impossibleHuman vectors.
     *  These methods are called after placing, removing or moving a piece
     *
     *  Parameters: pos1: The position where a piece was just placed
     *              pos2: The position where a piece was just removed
     */

    void updateHumanVectors(int pos1, int pos2, Board tempBoard);
    void updateAIVectors(int pos1, int pos2, Board tempBoard);

    /*!
     *  Methods that define the logic of the AI's turns.
     *  These methods are called before each AI turn
     */

    /*!
     *  Returns:    The position where the AI will place a piece next
     */

    int askPlacePosition(Board tempBoard);

    /*!
     *  Parameters: protectedPoints: All protected points on the board that cannot be removed
     *
     *  Returns:    The position where the AI will remove a piece next
     */

    int askRemovePosition(vector<int> protectedPoints);

    /*!
     *  Returns:    A pair of two integers: The positions from where and to where to AI will move a piece next
     */

    std::pair<int,int> askMovePositions();
    std::pair<int,int> askFreeMovePositions();

    /*!
     *  Determines whether the position pos2 can be reached by the AI player, and from where it can be reached
     *  This method is called when trying to form new mills in game phase 2
     *
     *  Parameters: pos2: The position that should be reached
     *
     *  Returns:    The position from where the position pos2 can be reached
     */

    int canBeReached(int pos2);

    /*!
     *  Resets the player
     *  This method is called when the "Restart game" button is pressed
     */

    void reset();

    private:
      int vertices[24];
      std::array<std::array<int, 3>, 16> possibleMillPositions;
      std::array<std::array<int, 2>, 32> edges; //adjacencies

      // These vectors contain the nrs of mill positions which have one piece/two pieces left until completed or are impossible
      // The AI uses these vectors to make decisions
      vector<int> onePieceLeft, twoPiecesLeft, impossible;
      vector<int> onePieceLeftHuman, twoPiecesLeftHuman, impossibleHuman;
};

#endif // BOARD_H
