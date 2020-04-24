#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King(int num, int letter, bool is_black);
	void print() override;
	bool try2move(int toNumber, int toLetter, void* boardPtr) override;
};