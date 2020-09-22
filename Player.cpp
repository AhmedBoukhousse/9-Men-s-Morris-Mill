#include "Player.h"

// argument constructor
Player::Player(int id)
{
  pieces = 9;
  this-> id = playerID;

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

int Player::getPiencesDisplayed()
{
  return piecesDisplayed.size();

}
