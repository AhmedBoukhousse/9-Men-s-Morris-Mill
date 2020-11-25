#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "board.h"

using namespace std;

class Move
{
   public:
        Move();
        int heuristique(int player, Board table, int p);
        int alphabeta1(int state[24],int depth,int ismax,int in,int alpha, int beta);
        void voisin(int i,vector<int>* v,int state[24],int with);
        int nbr_noeuds;

   private:
        int finaldepth;//leave this on 4 after testes

};

#endif // BOARD_H
