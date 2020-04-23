#pragma once
#include "Piece.h"
#include "Pawn.h"
#include <vector>
using namespace std;
class Board {
public:
	vector<vector<Piece *>> pieces_;
	bool black_turns_ = false;
	Board();
	
	void draw();
	bool turn();
};