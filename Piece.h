#pragma once
#include <iostream>
#include "math.h" // abs() 
constexpr auto black = true;
constexpr auto white = false;


class Piece {
protected:
	int num_;
	int letter_;
	bool firstMoveDone_ = false;
public:
	Piece(int num, int letter, bool);
	bool is_black_;
	virtual void print() = 0;
	bool move(int toNumber, int toLetter, void * board);
	virtual bool try2move(int toNumber, int toLetter, void * board) = 0;
};