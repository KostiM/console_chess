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

	bool will_be_check = ! move4try(toNumber,toLetter, board); // move2try checks if the move don`t cause check

	if (will_be_check) {
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

	bool will_not_be_check = !(board->black_turns_ ? board->check4check(black) : board->check4check(white));

	swap(board->pieces_[numBackup][letterBackup], board->pieces_[toNumber][toLetter]);
	num_ = numBackup;
	letter_ = letterBackup;
	if(toBackup)
		board->pieces_[toNumber][toLetter] = toBackup;
	return will_not_be_check;
}

std::ostream& operator<<(std::ostream& out, Piece const& piece)
{
	out << piece.name_ << ' ';
	out << piece.num_ << ' ';
	out << piece.letter_ << ' ';
	out << piece.is_black_ << ' ';
	out << piece.firstMoveDone_ << endl;
	return out;
}