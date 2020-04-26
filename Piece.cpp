#include "Piece.h"
#include "Board.h"

Piece::Piece(int num, int letter, bool is_black)
	: num_(num), letter_(letter), is_black_(is_black)
{
}

bool Piece::move(int toNumber, int toLetter, Board * board)
{
	if (board->pieces_[toNumber][toLetter] && is_black_ == board->pieces_[toNumber][toLetter]->is_black_) {
		cout << "You can not capture your own piece.\n";
		return false;
	}

	bool ok = move4try(toNumber,toLetter, board); // move2try checks if the move don`t cause check

	if (ok) {
		cout << "This move causes or do not avoid check! Please, try again mindfully.\n";
		return false;
	}
	
	
	if (board->pieces_[toNumber][toLetter]) {
		delete board->pieces_[toNumber][toLetter];
		board->pieces_[toNumber][toLetter] = 0;
	}
	
	swap(board->pieces_[num_][letter_], board->pieces_[toNumber][toLetter]);
	num_ = toNumber;
	letter_ = toLetter;
	if(!firstMoveDone_)
		firstMoveDone_ = true;
	cout << "The piece was successefully moved!\n";
	return true;
}

bool Piece::move4try(int toNumber, int toLetter, Board* board)
{
	if (board->pieces_[toNumber][toLetter] && is_black_ == board->pieces_[toNumber][toLetter]->is_black_) {
		return false;
	}
	Piece* toBackup = board->pieces_[toNumber][toLetter];
	if (toBackup)
		board->pieces_[toNumber][toLetter] = 0;

	int numBackup = num_;
	int letterBackup = letter_;

	swap(board->pieces_[numBackup][letterBackup], board->pieces_[toNumber][toLetter]);
	num_ = toNumber;
	letter_ = toLetter;

	bool ok = (board->black_turns_ ? board->check4check(black) : board->check4check(white));

	swap(board->pieces_[numBackup][letterBackup], board->pieces_[toNumber][toLetter]);
	num_ = numBackup;
	letter_ = letterBackup;

	board->pieces_[toNumber][toLetter] = toBackup;
	return ok;
}
