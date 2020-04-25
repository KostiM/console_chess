#include <iostream>
#include "Piece.h"
#include "Board.h"

using namespace std;

int main()
{
    Board board;
    while (true)
    {
        board.draw();
        while (!(board.turn())) {}
    }
    return 0;
}