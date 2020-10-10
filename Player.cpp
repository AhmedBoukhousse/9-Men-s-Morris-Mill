#include "Player.h"

// argument constructor
Player::Player(int id)
{
  piecesLeft = 9;
  this-> playerID = id;

}

// get the player ID
int Player::getPlayerId()
{
  return playerID;
}

//return how many pieces each player still have left!
int Player::getPiecesLeft()
{
  return piecesLeft;
}

int Player::getPiecesDisplayed()
{
  return piecesDisplayed.size();

}

vector<int> Player::getPiecesDisplayedVector()
{
  return piecesDisplayed;
}

void Player::increasePieces()
{
  piecesLeft++;
}

void Player::removePieces(int position)
{
  
  if(getPiecesDisplayed() > 0)
  {
    piecesDisplayed.erase(std::find(piecesDisplayed.begin(), piecesDisplayed.end(), position));
  }
  
}
  
 void Player::updateBoardPosition(int position1, int position2)
 {
   removePieces(position1);
   piecesLeft++;
   displayPiecesToBoard(position2);
   
 }
  
  void Player::displayPiecesToBoard(int position)
 {
    if(piecesLeft > 0)
    {
        piecesLeft--;
      piecesDisplayed.push_back(position);
    }
 }
 
  
bool Player::hasVolunerablePieces(vector<int> protectedPieces)
{
  for(vector<int>::iterator it = piecesDisplayed.begin(); it != piecesDisplayed.end(); ++it)
  {
    if(std::find(protectedPieces.begin(), protectedPieces.end(), *it) == protectedPieces.end()) return true;
  }
  return false;
}
bool Player::hasNoPieces()
{
  return piecesLeft == 0;
}
  
void Player::clearBoard()
{
  piecesDisplayed.clear();
  piecesLeft = 9;
}
