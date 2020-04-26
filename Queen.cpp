#include "Queen.h"
#include "Board.h"

Queen::Queen(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
	canBeCovered_ = true;
}

void Queen::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'Q';
}

bool Queen::try2move(int toNumber, int toLetter, Board* board)
{
	int deltaNumber = toNumber - num_;
	int deltaLetter = toLetter - letter_;

	if (abs(deltaNumber) == abs(deltaLetter)|| deltaLetter == 0 || deltaNumber == 0) {
		if (abs(deltaNumber) == abs(deltaLetter)) {
			if (deltaNumber > 0 && deltaLetter > 0) {
				for (int i = 1, j = 1; i < deltaNumber; ++i, ++j)
					if (board->pieces_[num_ + i][letter_ + j]) {
						//std::cout << "The queen can not move trough another piece.\n";
						return false;
					}
			}
			else if (deltaNumber > 0 && deltaLetter < 0) {
				for (int i = 1, j = -1; i < deltaNumber; ++i, --j)
					if (board->pieces_[num_ + i][letter_ + j]) {
						//std::cout << "The queen can not move trough another piece.\n";
						return false;
					}
			}
			else if (deltaNumber < 0 && deltaLetter > 0) {
				for (int i = -1, j = 1; j < deltaLetter; --i, ++j)
					if (board->pieces_[num_ + i][letter_ + j]) {
						//std::cout << "The queen can not move trough another piece.\n";
						return false;
					}
			}
			else {
				for (int i = -1, j = -1; j > deltaNumber; --i, --j)
					if (board->pieces_[num_ + i][letter_ + j]) {
						//std::cout << "The queen can not move trough another piece.\n";
						return false;
					}
			}
		}
		if (deltaLetter == 0 || deltaNumber == 0) {
			if (deltaLetter) {
				if (deltaLetter > 0) {
					for (int i = 1; i < deltaLetter; ++i) {
						if (board->pieces_[num_][letter_ + i]) {
							//std::cout << "The queen can not move trough another piece.\n";
							return false;
						}
					}
				}
				else {
					for (int i = -1; i > deltaLetter; --i) {
						if (board->pieces_[num_][letter_ + i]) {
							//std::cout << "The queen can not move trough another piece.\n";
							return false;
						}
					}
				}
			}
			else {
				if (deltaNumber > 0) {
					for (int i = 1; i < deltaNumber; ++i) {
						if (board->pieces_[num_ + i][letter_]) {
							//std::cout << "The queen can not move trough another piece.\n";
							return false;
						}
					}
				}
				else {
					for (int i = -1; i > deltaNumber; --i) {
						if (board->pieces_[num_ + i][letter_]) {
							//std::cout << "The queen can not move trough another piece.\n";
							return false;
						}
					}
				}
			}
		}
	}
	else {
		//std::cout << "The queen can not move there.\n";
		return false;
	}

	return true;
}
