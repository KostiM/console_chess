#include "Knight.h"
#include "Board.h"
#include<iostream>

Knight::Knight(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
}

void Knight::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'N';
}

bool Knight::try2move(int toNumber, int toLetter, void* boardPtr)
{
	Board* board = (Board*)boardPtr;
	int deltaNumber = toNumber - num_;
	int deltaLetter = toLetter - letter_;
	if ((abs(deltaNumber) == 2 && abs(deltaLetter) == 1) || (abs(deltaNumber) == 1 && abs(deltaLetter) == 2))
		return true;
	else{
		std::cout << "The knight can not move there.\n";
		return false;
	}
}
