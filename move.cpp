#include "move.h"
#include <iostream>

using namespace std;

int p1 = 1;
int p2 = 2;

bool legalmoves(int newlocation) // check location selected by the user
{
	
	if (newlocation == p1) {  // if it's taken
		return false;
	}
	else if (newlocation == p2) {
		return false;
	}
	else
		return true;
}

void movepiece(int prevlocation, int newlocation) // move piece to legal position
{
	if (legalmoves(newlocation) == true) {
		prevlocation = newlocation;			// piece moved to new location
	}
	else
		cout << "invalid move" << endl;

}
