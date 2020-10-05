#ifdef _HUMANPLAYER_H
#define _HUMANPLAYER_H

#define HUMAN_PLAYER_ID 1
#define HUMAN_PLAYER_ID 2
#include <iostream>
#include "Player.h"
using namespace std;

class HumanPlayer: public Player 
{
public: 
HumanPlayer();
int getPlayerID();

};
#endif //HUMANPLAYER_H
