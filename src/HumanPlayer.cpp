#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() : Player(HUMAN_PLAYER_ID) { }

int HumanPlayer::getPlayerID()
{
  return HUMAN_PLAYER_ID;
}
