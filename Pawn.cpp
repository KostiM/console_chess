#include "Pawn.h"

void Pawn::print()
{
	std::cout << (is_black_ ? 'B' : 'W') << ' ' << 'P';
}

Pawn::Pawn(bool black)
{
	is_black_ = black;
}

/*void Pawn::move(size_t row, size_t col)
{
	position_ = { row,col };
}*/
