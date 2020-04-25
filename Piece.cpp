#include "Piece.h"
#include "Board.h"

Piece::Piece(int num, int letter, bool is_black)
	: num_(num), letter_(letter), is_black_(is_black)
{
}

bool Piece::move(int toNumber, int toLetter, Board * board)
{
	if (board->pieces_[toNumber][toLetter])
		if (is_black_ != board->pieces_[toNumber][toLetter]->is_black_) {
			delete board->pieces_[toNumber][toLetter];
			board->pieces_[toNumber][toLetter] = 0;
		}
		else {
			cout << "You can not capture your own piece.\n";
			return false;
		}
	swap(board->pieces_[num_][letter_], board->pieces_[toNumber][toLetter]);
	num_ = toNumber;
	letter_ = toLetter;
	if(!firstMoveDone_)
		firstMoveDone_ = true;
	cout << "The piece was successefully moved!\n";
	return true;
}