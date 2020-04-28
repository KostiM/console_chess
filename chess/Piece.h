#pragma once
#include <iostream>
#include "math.h" // abs() 
constexpr auto black = true;
constexpr auto white = false;

class Board;

class Piece 
{
public:
	char name_;
	bool canBeCovered_ = false;
	int num_;
	int letter_;
	bool firstMoveDone_ = false;
	bool is_black_;
	Piece(int num, int letter, bool);
	
	virtual void print() = 0;
	virtual ~Piece() = default;

	bool move(int toNumber, int toLetter, Board * board);
	virtual bool try2move(int toNumber, int toLetter, Board* board) = 0;
	bool move4try(int toNumber, int toLetter, Board* board);

};

std::ostream& operator << (std::ostream& fout, Piece const& piece);
