#pragma once
#include "Piece.h"
#include <vector>
#include <algorithm> //  swap()

constexpr auto letters = "   a   b   c   d   e   f   g   h\n";
constexpr auto line = " ---------------------------------\n";
constexpr auto empty_cell = "   ";
enum letter { a, b, c, d, e, f, g, h };

letter char2letter(char);
using namespace std;

class Board {
private:
	int checkerNum_;
	int checkerLetter_;
public:
	vector<vector<Piece *>> pieces_;
	Piece* whiteKing_;
	Piece* blackKing_;
	bool black_turns_ = false;
	bool is_check = false;
	bool is_checkmate = false;
	
	Board();
	~Board();
	void reset();
	void draw();
	void save();
	bool load();
	bool turn();
	bool check4check(bool for_black);
	bool check4check(int num, int letter, bool for_black);
	bool check4mate(bool for_black);
	bool check4cover(Piece* king, Piece* checker);
	bool castling(int num, int letter);
	bool promotion(int num, int letter);
};