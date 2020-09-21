#ifndef _PLAYER_H
#define _PLAYER_H
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Player{
      Protected:
      int PlayerID;
      //string PlayerName;
      int piecesLeft;
      // a Vector to keep track of the number of pieces each player has that are displayed on board
      vector<int> piecesDisplayed;
      
      Public:
      Player(int id); // argument constructor
      int getId();
      int getPieces();
      int getPiecesDisplayed();
      int setPieces();
    
};
#endif
