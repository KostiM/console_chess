#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <algorithm> //swap()


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
    int fromLetter, toLetter;

    cout << "Enter your move (ex. b1 b2):";
    cin >> fromChar >> fromNumber >> toChar >> toNumber;
    cout << endl;
    if (fromChar > 'h' || fromChar < 'a' || toChar > 'h' || toChar < 'a' ||
        fromNumber < 1 || fromNumber > 8 || toNumber < 1 || toNumber > 8)
    {
        cout << "Your move is illegal! Please, try again.\n";
        return false;
    }
    fromLetter = char2letter(fromChar);
    toLetter = char2letter(toChar);
    --fromNumber;
    --toNumber;
    if (!pieces_[fromNumber][fromLetter])
    {
        cout << "Your move is illegal! Please, try again.\n";
        return false;
    }
    if (black_turns_ != pieces_[fromNumber][fromLetter]->is_black_)
    {
        cout << "You can not move oppenent`s piece.\n";
        return false;
    }
    if (fromLetter == toLetter && fromNumber == toNumber) {
        cout << "Current position must be different from desired position.\n";
        return false;
    }

    if (fromLetter == e && abs(toLetter - fromLetter) == 2
        && (fromNumber == 0 || fromNumber == 7) && (toNumber - fromNumber) == 0) { // check for castling
        if (is_check) {
            cout << "You can not do castling when your king is checked!";
            return 0;
        }

        if (castling(toNumber, toLetter)) {}
        else
            return false;
    }
    else {
        if (pieces_[fromNumber][fromLetter]->try2move(toNumber, toLetter, this))
            if (pieces_[fromNumber][fromLetter]->move(toNumber, toLetter, this)) {}
            else
                return false;
        else {
            cout << "This is illegal move! Please, try again mindfully.\n";
            return false;
        }
    }
    black_turns_ = !black_turns_;

    is_check = check4check(black_turns_);

    if (is_check) {
        is_checkmate = check4mate(black_turns_);
    }

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

bool Board::check4check(bool for_black)
{
    Piece* king = (for_black ? blackKing_ : whiteKing_);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (pieces_[i][j] && pieces_[i][j]->is_black_ != for_black
                && pieces_[i][j]->try2move(king->num_, king->letter_, this))
            {
                checkerNum_ = i;
                checkerLetter_ = j;
                return true;
            }

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

bool Board::check4mate(bool for_black)
{
    //check if any allied piece can capture the checker
    for(int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if(pieces_[i][j] && pieces_[i][j]->is_black_ == for_black)
                if (pieces_[i][j]->try2move(checkerNum_, checkerLetter_, this)
                    && pieces_[i][j]->move4try(checkerNum_, checkerLetter_, this))
                    return false;

    //check if king can move to avoid the check
    Piece* king = (for_black ? blackKing_ : whiteKing_);

    for (int i = -1; i < 2; ++i)
        for (int j = -1; j < 2; ++j)
            if (i || j)
                if (king->try2move(king->num_ + i, king->letter_ + j, this) && king->move4try(king->num_ + i, king->letter_ + j, this))
                    return false;

    // check if any piece can cover the king

    check4check(for_black); // in order to update checkerNum_ and checkerLetter_
    if (!check4cover(king, pieces_[checkerNum_][checkerLetter_]))
        return false;


    return true;
}

bool Board::check4cover(Piece* king, Piece* checker)
{
    if (checker->canBeCovered_) {
        int deltaNumber = king->num_ - checker->num_;
        int deltaLetter = king->letter_ - checker->letter_;

        if (abs(deltaNumber) == 1 || abs(deltaLetter) == 1)
            return false;


        if (abs(deltaNumber) == abs(deltaLetter)) {
            if (deltaNumber > 0 && deltaLetter > 0) {
                for (int n = 1, l = 1; n < deltaNumber; ++n, ++l)
                    for (int i = 0; i < 8; ++i)
                        for (int j = 0; j < 8; ++j)
                            if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_ + l, this)
                                    && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_ + l, this))
                                    return true;
            }
            else if (deltaNumber > 0 && deltaLetter < 0) {
                for (int n = 1, l = -1; n < deltaNumber; ++n, --l)
                    for (int i = 0; i < 8; ++i)
                        for (int j = 0; j < 8; ++j)
                            if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_ + l, this)
                                    && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_ + l, this))
                                    return true;
            }
            else if (deltaNumber < 0 && deltaLetter > 0) {
                for (int n = -1, l = 1; l < deltaLetter; --n, ++l)
                    for (int i = 0; i < 8; ++i)
                        for (int j = 0; j < 8; ++j)
                            if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_ + l, this)
                                    && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_ + l, this))
                                    return true;
            }
            else {
                for (int n = -1, l = -1; l > deltaNumber; --n, --l)
                    for (int i = 0; i < 8; ++i)
                        for (int j = 0; j < 8; ++j)
                            if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_ + l, this)
                                    && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_ + l, this))
                                    return true;
            }
        }


        if (deltaLetter == 0 || deltaNumber == 0) {
            if (deltaLetter) {
                if (deltaLetter > 0) {
                    for (int l = 1; l < deltaLetter; ++l)
                        for (int i = 0; i < 8; ++i)
                            for (int j = 0; j < 8; ++j)
                                if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                    if (pieces_[i][j]->try2move(checker->num_, checker->letter_ + l, this)
                                        && pieces_[i][j]->move4try(checker->num_, checker->letter_ + l, this))
                                        return true;
                }
                else {
                    for (int l = -1; l > deltaLetter; --l)
                        for (int i = 0; i < 8; ++i)
                            for (int j = 0; j < 8; ++j)
                                if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                    if (pieces_[i][j]->try2move(checker->num_, checker->letter_ + l, this)
                                        && pieces_[i][j]->move4try(checker->num_, checker->letter_ + l, this))
                                        return true;
                }
            }
            else {
                if (deltaNumber > 0) {
                    for (int n = 1; n < deltaNumber; ++n)
                        for (int i = 0; i < 8; ++i)
                            for (int j = 0; j < 8; ++j)
                                if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                    if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_, this)
                                        && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_, this))
                                        return true;
                }
                else {
                    for (int n = -1; n > deltaNumber; --n)
                        for (int i = 0; i < 8; ++i)
                            for (int j = 0; j < 8; ++j)
                                if (pieces_[i][j] && pieces_[i][j]->is_black_ == king->is_black_)
                                    if (pieces_[i][j]->try2move(checker->num_ + n, checker->letter_, this)
                                        && pieces_[i][j]->move4try(checker->num_ + n, checker->letter_, this))
                                        return true;
                }
            }

        }
    }
    else {
        return false;
    }
}

bool Board::castling(int num, int letter)
{
    if (pieces_[num][e]->firstMoveDone_) {
        cout << "Castling is not allowed. The king have already moved.\n";
        return false;
    }

    if (letter == g) {  //short castling
        if (pieces_[num][h]->firstMoveDone_) {
            cout << "Castling is illegal. The rook have already moved.\n";
            return false;
        }

        if (pieces_[num][f] || pieces_[num][g])
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        if (check4check(num, f, black_turns_) || check4check(num, g, black_turns_))
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        pieces_[num][e]->move(num, g, this);
        pieces_[num][h]->move(num, f, this);
    }
    else { // letter == c long castlig
        if (pieces_[num][a]->firstMoveDone_) {
            cout << "Castling is illegal. The rook have already moved.\n";
            return false;
        }

        if (pieces_[num][b] || pieces_[num][c] || pieces_[num][d])
        {
            cout << "Castling is illegal.\n";
            return false;
        }

        if (check4check(num, c, black_turns_) || check4check(num, d, black_turns_))
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        pieces_[num][e]->move(num, c, this);
        pieces_[num][a]->move(num, d, this);

    }
    
    return true;
}
