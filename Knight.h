#pragma once
#include "Piece.h"
class Knight : public Piece{
public:
	Knight(int num, int letter, bool is_black);
	void print() override;
	bool try2move(int toNumber, int toLetter, void* board) override;
};