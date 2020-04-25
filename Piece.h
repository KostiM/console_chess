#pragma once
#include <iostream>
#include "math.h" // abs() 
constexpr auto black = true;
constexpr auto white = false;

class Board;

class Piece 
{
public:
	int num_;
	int letter_;
	bool firstMoveDone_ = false;
	Piece(int num, int letter, bool);
	bool is_black_;
	virtual void print() = 0;
	bool move(int toNumber, int toLetter, Board * board);
	virtual bool try2move(int toNumber, int toLetter, Board* board) = 0;
	virtual ~Piece() = default;
};