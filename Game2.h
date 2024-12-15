#ifndef GAME_NUMBER_2_GAME2_H
#define GAME_NUMBER_2_GAME2_H
#include "BoardGame_Classes.h"


class Game2_Board : public Board<char> {

public:
    Game2_Board();
    bool update_board(int x, int y, char symbol) ;
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int minimax(int &x, int &y, bool is_max, bool first);
    ~Game2_Board();
};


class Game2_Player : public Player<char> {
public:
    Game2_Player(string name, char symbol);
    void getmove(int& x,int& y);
};


class Game2_RandomPlayer : public RandomPlayer<char> {
private:
    int dimension2;

public:
    Game2_RandomPlayer(char symbol);
    void getmove(int& x,int& y);

};

class Game2_AIPlayer : public Player<char> {
protected:
    Game2_Board* board;
public:
    Game2_AIPlayer(char symbol, Game2_Board* board);
    void getmove(int& x,int& y);
};




#endif
