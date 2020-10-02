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
      int getPlayerId();
      int getPiecesLeft();
      int getPiecesDisplayed();
      int <int> getPiecesDisplayedVector();
      
      // setter functions
      void increasePieces();
      
      
      //Update the state of the pieces displayed on board
      void displayPiecesOnBoard(int position);
      void removePieces(int position);
      
      //This function should be called if the oppoent forms a Mill. 
      //it checks if the player has any pieces that are volunerable and can be removed. 
      //if no pieces are vulnerable then the opponet will not be allowed to remove any pieces
      // return true if the player's pieces on board meet the requirement to be removed (not in a Mill or in a mill but the last 3 pieces)
      bool hasVolunerablePieces(vector<int> protectedPieces);
      
      /* the hasNoPieces checks if a certain player is out of pieces 
      */
      bool hasNoPieces();
      
      // reset the game if the restart button is pressed
      void reset();
    
};
#endif //PLAYER
