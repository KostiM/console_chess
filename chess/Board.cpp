#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <algorithm>
#include <fstream>
#include <string>//swap()



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

void Board::reset()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            delete pieces_[i][j];
            pieces_[i][j] = 0;
        }
    black_turns_ = false;
    is_check = false;
    is_checkmate = false;
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

void Board::save()
{
    ofstream fout;
    fout.open("chess_saved_data.txt");
    if (fout.is_open()) {
        fout << black_turns_ << endl;
        fout << is_check << endl;
        for(int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                
                if (pieces_[i][j])
                    fout << *pieces_[i][j];
            }
    }
    fout.close();
}

bool Board::load()
{
    ifstream fin;
    fin.open("chess_saved_data.txt");
    if (fin.is_open()) {
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                delete pieces_[i][j];
                pieces_[i][j] = 0;
            }
        blackKing_ = 0;
        whiteKing_ = 0;
        fin >> black_turns_ >> is_check ;
        char name;
        int num, letter;
        bool is_black, firstmovedone;
        while (fin >> name >> num >> letter >> is_black >> firstmovedone) {
            switch (name)
            {
            case'p': {
                pieces_[num][letter] = new Pawn(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                break;
            }
            case'n': {
                pieces_[num][letter] = new Knight(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                break;
            }
            case'r': {
                pieces_[num][letter] = new Rook(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                break;
            }
            case'b': {
                pieces_[num][letter] = new Bishop(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                break;
            }
            case'q': {
                pieces_[num][letter] = new Queen(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                break;
            }
            case'k': {
                pieces_[num][letter] = new King(num, letter, is_black);
                if (firstmovedone)
                    pieces_[num][letter]->firstMoveDone_ = firstmovedone;
                (is_black ? blackKing_ : whiteKing_) = pieces_[num][letter];
                break;
            }
            }
        }
        fin.close();
        return true;
    }
    else
        return false;
    
}

bool Board::turn()
{
    char fromChar, toChar;
    int fromNumber, toNumber;
    int fromLetter, toLetter;
    cout << "Enter your move (ex. b1 b2):";
    string move;
    getline(cin, move);
    move.erase(std::remove(move.begin(), move.end(), ' '), move.end());
    if (move.size() < 4) {
        cout << "Invalid input! Please, try again according to the example.\n";
        return false;
    }
    fromChar = move.at(0);
    fromNumber = move.at(1) - '0';
    toChar = move.at(2);
    toNumber = move.at(3) - '0';
    if (fromChar > 'h' || fromChar < 'a' || toChar > 'h' || toChar < 'a' ||
        fromNumber < 1 || fromNumber > 8 || toNumber < 1 || toNumber > 8)
    {
        cout << "Invalid input! Please, try again according to the example.\n";
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
        && (fromNumber == 0 || fromNumber == 7) && (toNumber - fromNumber) == 0 && pieces_[fromNumber][fromLetter]->name_ == 'k') { // check for castling
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
            if (pieces_[fromNumber][fromLetter]->move(toNumber, toLetter, this)) {
                if((toNumber == 0 || toNumber == 7) && pieces_[toNumber][toLetter]->name_ == 'p')
                    while (!promotion(toNumber,toLetter)) {}
            }
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
    check4check(for_black);
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
            if (i || j) {
                int toNumber = king->num_ + i;
                int toLetter = king->letter_ + j;
                if (toNumber >= 0 && toNumber <= 7 && toLetter >= 0 && toLetter <= 7)
                    if (king->try2move(toNumber, toLetter, this) && king->move4try(toNumber, toLetter, this))
                        return false;
            }

    // check if any piece can cover the king

    check4check(for_black); // in order to update checkerNum_ and checkerLetter_
    if (check4cover(king, pieces_[checkerNum_][checkerLetter_]))
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
    
    return false;
}

bool Board::castling(int num, int letter)
{
    if (pieces_[num][e] && pieces_[num][e]->firstMoveDone_) {
        cout << "Castling is not allowed. The king have already moved.\n";
        return false;
    }

    if (letter == g) {  //short castling
        if (pieces_[num][h] && pieces_[num][h]->firstMoveDone_) {
            cout << "Castling is illegal. The rook have already moved.\n";
            return false;
        }

        if (pieces_[num][f] || pieces_[num][g])
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        if (check4check(num, f, (num == 0 ? white : black)) || check4check(num, g, (num == 0 ? white : black)))
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        pieces_[num][e]->move(num, g, this);
        pieces_[num][h]->move(num, f, this);
    }
    else { // letter == c long castlig
        if (pieces_[num][a] && pieces_[num][a]->firstMoveDone_) {
            cout << "Castling is illegal. The rook have already moved.\n";
            return false;
        }

        if (pieces_[num][b] || pieces_[num][c] || pieces_[num][d])
        {
            cout << "Castling is illegal.\n";
            return false;
        }

        if (check4check(num, c, (num == 0 ? white : black)) || check4check(num, d, (num == 0 ? white : black)))
        {
            cout << "Castling is illegal.\n";
            return false;
        }
        pieces_[num][e]->move(num, c, this);
        pieces_[num][a]->move(num, d, this);

    }
    
    return true;
}

bool Board::promotion(int num, int letter)
{
    cout << "It`s pawn promotion.\nWhat piece whould you like to get? (Queen[Q], Rook[R], Bishop[B], Knight[N]):";
    delete pieces_[num][letter];
    pieces_[num][letter] = 0;

    string choice;
    getline(cin, choice);
    choice.erase(std::remove(choice.begin(), choice.end(), ' '), choice.end());
    if (choice == "Queen" || choice == "Q" || choice == "q")
    {
        pieces_[num][letter] = new Queen(num, letter, black_turns_);
    }
    else if (choice == "Rook" || choice == "R" || choice == "r")
    {
        pieces_[num][letter] = new Rook(num, letter, black_turns_);
    }
    else if (choice == "Bishop" || choice == "B" || choice == "b")
    {
        pieces_[num][letter] = new Bishop(num, letter, black_turns_);
    }
    else if (choice == "Knight" || choice == "N" || choice == "n")
    {
        pieces_[num][letter] = new Knight(num, letter, black_turns_);
    }
    else
    {
        cout << "Invalid input. Please, try again.\n";
        return false;
    }
    return true;
}
