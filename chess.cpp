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
        if (board.black_turns_)
            cout << "Black`s turn!\n";
        else
            cout << "White`s turn!\n";
        if (board.is_check)
            cout << "You`ve got a check!\n";
        while (!(board.turn())) {}
    }
    return 0;
}