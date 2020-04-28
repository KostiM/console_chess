#include <iostream>
#include <string>
#include "Piece.h"
#include "Board.h"

using namespace std;

char userChoose();


int main()
{
    Board board;
    board.draw();
    char choice;
    bool saved = false;
    bool loaded = false;
    bool notloaded = false;
    
    cout <<  "White`s turn!\n";

    while ((choice = userChoose()) != 'e')
    {
        switch (choice)
        {
        case 'm': {
            if (board.is_checkmate)
                break;
            while (!(board.turn())) {
            }
            break;
        }
        case 's': {
            if (board.is_checkmate)
                break;
            board.save();
            saved = true;
            break;
        }
        case 'l': {
            if (board.load())
                loaded = true;
            else
                notloaded = true;
            break;
        }
        case 'r': {
            board.reset();
            break;
        }
        }
        board.draw();
        if (board.is_checkmate) {
            cout << (board.black_turns_ ? "White win!\n" : "Black win!\n");
            cout << "The game is over! You can start new by restart or load saved one!\n";
        }
        else {
            if (saved) {
                cout << "The game is successfully saved.\nPlease, don`t delete \"chess_saved_data.txt\".\n";
                saved = false;
            }
            if (loaded) {
                cout << "The game is successfully loaded.\n";
                loaded = false;
            }
            if (notloaded) {
                cout << "The game can not be loaded, \"chess_saved_data.txt\". is missing.\n";
                notloaded = false;
            }
            cout << (board.black_turns_ ? "Black`s turn!\n" : "White`s turn!\n");
            if (board.is_check)
                cout << "You`ve got a check!\n";
        }
    }
    return 0;
}

char userChoose() {
    string choice;
    cout << "What do you want to do now? (Move[M], Restart[R], Save[S], Load[L], Exit[E]):";
    getline(cin,choice);
    choice.erase(std::remove(choice.begin(), choice.end(), ' '), choice.end());
    char result = '0';
    if (choice == "Move" || choice == "M" || choice == "m")
    {
        result = 'm';
    }
    else if (choice == "Restart" || choice == "R" || choice == "r")
    {
        result = 'r';
    }
    else if (choice == "Save" || choice == "S" || choice == "s")
    {
        result = 's';
    }
    else if (choice == "Load" || choice == "L" || choice == "l")
    {
        result = 'l';
    }
    else if (choice == "Exit" || choice == "E" || choice == "e")
    {
        result = 'e';
    }
    return result;
}