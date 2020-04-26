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
        if (board.is_checkmate) {
            cout << (board.black_turns_ ? "White win!\n" : "Black win!\n");
            break;
        }
        cout << (board.black_turns_ ? "Black`s turn!\n" : "White`s turn!\n");
        if (board.is_check)
            cout << "You`ve got a check!\n";
        while (!(board.turn())) {}
    }
    system("pause");
    return 0;
}