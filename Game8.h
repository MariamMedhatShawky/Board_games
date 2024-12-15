#ifndef GAME_NUMBER_2_GAME8_H
#define GAME_NUMBER_2_GAME8_H

#include "BoardGame_Classes.h"

class Game8_MiniBoard : public Board<char> {
public:
    Game8_MiniBoard(); // Constructor to initialize the board
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    char get_symbol(int x, int y);
};


class Game8_MainBoard : public Board<char> {
private:
    Game8_MiniBoard* boards[3][3]; // A 3x3 array of TicTacToeBoard
public:
    Game8_MainBoard(); // Constructor to initialize the boards
    ~Game8_MainBoard(); // Destructor to clean up the TicTacToeBoards
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


class Game8_Player : public Player<char> {
public:
    Game8_Player(string name, char symbol);
    void getmove(int& x, int& y);
};


class Game8_RandomPlayer : public RandomPlayer<char> {
public:
    Game8_RandomPlayer(char symbol);
    void getmove(int& x, int& y);
};



#endif //GAME_NUMBER_2_GAME8_H
