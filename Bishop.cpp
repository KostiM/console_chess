#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
	canBeCovered_ = true;
}

void Bishop::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'B';
}

bool Bishop::try2move(int toNumber, int toLetter, Board* board)
{
	int deltaNumber = toNumber - num_;
	int deltaLetter = toLetter - letter_;

	if ( abs(deltaNumber) == abs(deltaLetter) ){
		if (deltaNumber > 0 && deltaLetter > 0) {
			for (int i = 1, j = 1; i < deltaNumber ; ++i, ++j)
				if (board->pieces_[num_ + i][letter_ + j]) {
					//std::cout << "The bishop can not move trough another piece.\n";
					return false;
				}
		}
		else if (deltaNumber > 0 && deltaLetter < 0) {
			for (int i = 1, j = -1; i < deltaNumber; ++i, --j)
				if (board->pieces_[num_ + i][letter_ + j]) {
					//std::cout << "The bishop can not move trough another piece.\n";
					return false;
				}
		}
		else if (deltaNumber < 0 && deltaLetter > 0) {
			for (int i = -1, j = 1; j < deltaLetter; --i, ++j)
				if (board->pieces_[num_ + i][letter_ + j]) {
					//std::cout << "The bishop can not move trough another piece.\n";
					return false;
				}
		}
		else {
			for (int i = -1, j = -1; j > deltaNumber; --i, --j)
				if (board->pieces_[num_ + i][letter_ + j]) {
					//std::cout << "The bishop can not move trough another piece.\n";
					return false;
				}
		}
	}
	else {
		//std::cout << "The bishop can not move there.\n";
		return false;
	}
	return true;
}
