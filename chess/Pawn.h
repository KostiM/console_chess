#pragma once
#include "Piece.h"
class Pawn : public Piece 
{	
public:
	Pawn(int num,int letter,bool is_black);
	void print() override;
	bool try2move(int toNumber, int toLetter, Board* board) override;
};