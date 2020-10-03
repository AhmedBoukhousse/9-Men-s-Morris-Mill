#include "move.h"
#include <iostream>

using namespace std;

char taken = 'X';

bool legalmoves(int newlocation) // check location selected by the user
{
	
	if (newlocation == taken) {  // if it's taken
		return false;
	}
	else
		return true;
}

void movepiece(int prevlocation, int newlocation) // move piece to legal position
{
	if (legalmoves(newlocation) == true) {
		newlocation = taken;			// piece moved to new location
	}
	else
		cout << "invalid move" << endl;

}
