#include "King.h"
#include "Board.h"

King::King(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
	name_ = 'k';
}

void King::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'K';
}


bool King::try2move(int toNumber, int toLetter, Board* board)
{
	int deltaNumber = abs(toNumber - num_);
	int deltaLetter = abs(toLetter - letter_);
	if ((deltaNumber == 1 && deltaLetter == 1) || (deltaNumber == 0 && deltaLetter == 1) 
		|| (deltaNumber == 1 && deltaLetter == 0) ) {
		
	}
	else {
		//std::cout << "The king can not move there.\n";
		return false;
	}
	return true;
}
