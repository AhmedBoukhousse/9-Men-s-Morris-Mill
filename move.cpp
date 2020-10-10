#include "move.h"
#include <iostream>

using namespace std;

int p1 = 1;
int p2 = 2;

// check location selected by the user
bool legalmoves(int newlocation) {

		// if it's taken
	if (newlocation == p1) {
		return false;
	}

	else if (newlocation == p2) {
		return false;
	}

	else if (newlocation == 0)
		return true;

	else
		return false;
	
}

// move piece to legal position
void movepiece(int prevlocation, int newlocation) 
{
	if (legalmoves(newlocation) == true) {
		// piece moved to new location
		int temp;
		temp = prevlocation;  // store location before moving piece
		prevlocation = newlocation;	   
		temp = 0;   // the old location becomes empty 
	}
	else
		cout << "invalid move" << endl;

}
