#include "Board.h"
#include "Pawn.h"
#include "Knight.h"


Board::Board()
{
    pieces_.reserve(8);
    for (int i = 0; i < 8; ++i)
        pieces_.push_back(vector<Piece *>(8, 0));
    for (int i = 0; i < 8; ++i) {
        pieces_[1][i] = new Pawn(1, i, white);
        pieces_[6][i] = new Pawn(6, i, black);
    }
    pieces_[0][1] = new Knight(0, 1, white);
    pieces_[0][6] = new Knight(0, 6, white);
    pieces_[7][1] = new Knight(7, 1, black);
    pieces_[7][6] = new Knight(7, 6, black);
}

void Board::draw()
{
    system("cls");
    cout << "               White\n";
    cout << letters;
    cout << line;
    for (int r = 0; r < 8; ++r) {
        cout << r+1  << '|';
        for (int c = 0; c < 8; ++c) {
            if (pieces_[r][c] == 0)
                cout << empty_cell;
            else
                pieces_[r][c]->print();
            cout << '|';
        }
        cout << r+1  << endl;
        cout << line;
    }
    cout << letters;
    cout << "               Black\n";
}

bool Board::turn()
{
    char fromChar, toChar;
    int fromNumber, toNumber;
    letter fromLetter, toLetter;
    if (black_turns_) cout << "Black`s turn! ";
    else cout << "White`s turn! ";
    cout << "Enter your move(ex. b1 b2):";
    cin >> fromChar >> fromNumber >> toChar >> toNumber;
    cout << endl;
    if (fromChar > 'h' || fromChar < 'a' || toChar > 'h' || toChar < 'a' ||
        fromNumber < 1 || fromNumber > 8 || toNumber < 1 || toNumber > 8)
    {
        cout << "You entered incorrect move! Please try again!\n";
        return false;
    }
    fromLetter = char2letter(fromChar);
    toLetter = char2letter(toChar);
    --fromNumber;
    --toNumber;
    if (((!black_turns_) && pieces_[fromNumber][fromLetter]->is_black_) ||
        (black_turns_ && (!pieces_[fromNumber][fromLetter]->is_black_))) 
    {
        cout << "You can not move oppenent`s piece!\n";
        return false;
    }
    if (fromLetter == toLetter && fromNumber == toNumber) {
        cout << "Current position must be different from desired position!\n";
        return false;
    }

    if (pieces_[fromNumber][fromLetter]->try2move(toNumber, toLetter, this))
        if (pieces_[fromNumber][fromLetter]->move(toNumber, toLetter, this)) {}
        else
            return false;
    else
        return false;

    black_turns_ = !black_turns_;
    return true;
}

letter char2letter(char ch)
{
    letter l;
    switch (ch)
    {
    case 'a': {
        l = a;
        break;
    }
    case 'b': {
        l = b;
        break;
    }
    case 'c': {
        l = c;
        break;
    }
    case 'd': {
        l = d;
        break;
    }
    case 'e': {
        l = e;
        break;
    }
    case 'f': {
        l = f;
        break;
    }
    case 'g': {
        l = g;
        break;
    }
    case 'h': {
        l = h;
        break;
    }
    }
    return l;
}
