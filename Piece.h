#pragma once
#include <iostream>
#include "Position.h"

class Piece {
public:
	bool is_black_ = true;
	//Position position_ = Position(0,0);
	//Position & getPosition() { return position_; }
	//explicit Piece(size_t row = 0,size_t col = 0, bool black = true ) : position_(row,col), is_black_(black){}
	virtual void print() = 0;
	//virtual void move(size_t , size_t) = 0;
};