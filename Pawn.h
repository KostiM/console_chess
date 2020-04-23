#pragma once
#include "Piece.h"
class Pawn : public Piece {
public:
	void print() override;
	Pawn(bool black);
	//void move(size_t row, size_t col) override;
};