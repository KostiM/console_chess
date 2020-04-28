#include "Rook.h"
#include "Board.h"

Rook::Rook(int num, int letter, bool is_black)
	: Piece(num, letter, is_black)
{
	canBeCovered_ = true;
	name_ = 'r';
}

void Rook::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'R';
}

bool Rook::try2move(int toNumber, int toLetter, Board* board)
{
	int deltaNumber = toNumber - num_;
	int deltaLetter = toLetter - letter_;

	if (deltaLetter == 0 || deltaNumber == 0) {
		if (deltaLetter) { 
			if (deltaLetter > 0) {
				for (int i = 1; i < deltaLetter; ++i) {
					if (board->pieces_[num_][letter_ + i]) {
						//std::cout << "The rook can not move trough another piece.\n";
						return false;
					}
				}
			}
			else {
				for (int i = -1; i > deltaLetter; --i) {
					if (board->pieces_[num_][letter_ + i]) {
						//std::cout << "The rook can not move trough another piece.\n";
						return false;
					}
				}
			}
		}
		else {
			if (deltaNumber > 0) {
				for (int i = 1; i < deltaNumber; ++i) {
					if (board->pieces_[num_ + i][letter_ ]) {
						//std::cout << "The rook can not move trough another piece.\n";
						return false;
					}
				}
			}
			else {
				for (int i = -1; i > deltaNumber; --i) {
					if (board->pieces_[num_ + i][letter_]) {
						//std::cout << "The rook can not move trough another piece.\n";
						return false;
					}
				}
			}
		}
		
	}
	else {
		//std::cout << "The rook can not move there.\n";
		return false;
	}
	return true;
}
