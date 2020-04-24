#pragma once
#include "Piece.h"
#include <vector>
#include <algorithm> //  swap()

constexpr auto letters = "   a   b   c   d   e   f   g   h\n";
constexpr auto line = " --------------------------------\n";
constexpr auto empty_cell = "   ";
enum letter { a, b, c, d, e, f, g, h };

letter char2letter(char);
using namespace std;
class Board {
public:
	vector<vector<Piece *>> pieces_;
	bool black_turns_ = false;
	Board();

	void draw();
	bool turn();
};