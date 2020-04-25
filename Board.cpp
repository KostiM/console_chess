#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


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
    pieces_[0][0] = new Rook(0, 0, white);
    pieces_[0][7] = new Rook(0, 7, white);
    pieces_[7][0] = new Rook(7, 0, black);
    pieces_[7][7] = new Rook(7, 7, black);
    pieces_[0][2] = new Bishop(0, 2, white);
    pieces_[0][5] = new Bishop(0, 5, white);
    pieces_[7][2] = new Bishop(7, 2, black);
    pieces_[7][5] = new Bishop(7, 5, black);
    pieces_[0][3] = new Queen(0, 3, white);
    pieces_[7][3] = new Queen(7, 3, black);
    pieces_[0][4] = new King(0, 4, white);
    whiteKing_ = pieces_[0][4];
    pieces_[7][4] = new King(7, 4, black);
    blackKing_ = pieces_[7][4];

}

Board::~Board()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            delete pieces_[i][j];
}

bool Board::check4check(bool for_black) 
{
    Piece * king = ( for_black ? blackKing_ : whiteKing_);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (pieces_[i][j] && pieces_[i][j]->is_black_ != for_black
                && pieces_[i][j]->try2move(king->num_, king->letter_, this))
                return true;

    return false;
}

bool Board::check4check(int num, int letter, bool for_black)
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (pieces_[i][j] && pieces_[i][j]->is_black_ != for_black
                && pieces_[i][j]->try2move(num, letter, this))
                return true;

    return false;
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
    if (black_turns_) 
        cout << "Black`s turn!\n";
    else 
        cout << "White`s turn!\n";
    if (is_check)
        cout << "You`ve got a check!\n";

    cout << "Enter your move (ex. b1 b2):";
    cin >> fromChar >> fromNumber >> toChar >> toNumber;
    cout << endl;
    if (fromChar > 'h' || fromChar < 'a' || toChar > 'h' || toChar < 'a' ||
        fromNumber < 1 || fromNumber > 8 || toNumber < 1 || toNumber > 8)
    {
        cout << "You entered incorrect move! Please, try again.\n";
        return false;
    }
    fromLetter = char2letter(fromChar);
    toLetter = char2letter(toChar);
    --fromNumber;
    --toNumber;
    if (((!black_turns_) && pieces_[fromNumber][fromLetter]->is_black_) ||
        (black_turns_ && (!pieces_[fromNumber][fromLetter]->is_black_))) 
    {
        cout << "You can not move oppenent`s piece.\n";
        return false;
    }
    if (fromLetter == toLetter && fromNumber == toNumber) {
        cout << "Current position must be different from desired position.\n";
        return false;
    }

    if (pieces_[fromNumber][fromLetter]->try2move(toNumber, toLetter, this))
        if (pieces_[fromNumber][fromLetter]->move(toNumber, toLetter, this)) {}
        else
            return false;
    else {
        cout << "This is illegal move! Please, try again mindfully.";
        return false;
    }

    black_turns_ = !black_turns_;

    is_check = check4check(black_turns_);

    if (is_check) {}         // continue check for checkmate

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
