#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(int num, int letter, bool is_black)
	:Piece(num, letter, is_black)
{
	name_ = 'p';
}

void Pawn::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'P';
}

bool Pawn::try2move(int toNumber, int toLetter, Board* board)
{
	int deltaNumber = toNumber - num_;
	int deltaLetter = toLetter - letter_;
	if (is_black_) {
		if ( (!deltaLetter) && (board->pieces_[toNumber][toLetter] == 0) && 
		( (deltaNumber == -1) || (( deltaNumber == -2) && !firstMoveDone_ && board->pieces_[num_ - 1][letter_] == 0 )))
			return true;
		if (deltaNumber == -1 && abs(deltaLetter) == 1 && board->pieces_[toNumber][toLetter] != 0)
			return true;
	}
	else {
		if ((!deltaLetter) && (board->pieces_[toNumber][toLetter] == 0) &&
			((deltaNumber == 1) || ((deltaNumber == 2) && !firstMoveDone_ && board->pieces_[num_ + 1][letter_] == 0)))
			return true;
		if (deltaNumber == 1 && abs(deltaLetter) == 1 && board->pieces_[toNumber][toLetter] != 0)
			return true;
	}
	
	//cout << "The pawn can not move there.\n";
	return false;
}
