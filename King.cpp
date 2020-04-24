#include "King.h"
#include "Board.h"
#include <iostream>

King::King(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
}

void King::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'K';
}


bool King::try2move(int toNumber, int toLetter, void* boardPtr)
{
	Board* board = (Board*)boardPtr;
	int deltaNumber = abs(toNumber - num_);
	int deltaLetter = abs(toLetter - letter_);
	if ((deltaNumber == 1 && deltaLetter == 1) || (deltaNumber == 0 && deltaLetter == 1) 
		|| (deltaNumber == 1 && deltaLetter == 0) ) {
		
	}
	else {
		std::cout << "The king can not move there.\n";
		return false;
	}
	return true;
}
