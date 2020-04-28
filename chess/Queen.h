#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int num, int letter, bool is_black);
	void print() override;
	bool try2move(int toNumber, int toLetter, Board* board) override;
};