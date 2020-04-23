#include <iostream>
#include "Position.h"
#include "Piece.h"
#include "Pawn.h"
#include "Board.h"

using namespace std;

int main()
{
    Board board;
    Pawn bpawn(true);
    Pawn wpawn(false);
    for (int i = 0; i < 8; ++i) {
        board.pieces_[1][i] = &bpawn;
        board.pieces_[6][i] = &wpawn;
    }
    while (true)
    {
        board.draw();
        while (!(board.turn())) {}
    }
    
    
    return 0;
}


