#ifndef GAME_NUMBER_2_GAME5_H
#define GAME_NUMBER_2_GAME5_H
#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


class Game5_Board : public Board<int> {
public:
    Game5_Board();
    bool update_board(int x, int y, int symbol) ;
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    ~Game5_Board();
};

class Game5_Player : public Player<int> {
protected:
    vector<int> available_numbers;
public:
    Game5_Player(string name, int symbol, vector<int> numbers) ;
    void getmove(int& x,int& y);

};


class Game5_RandomPlayer : public RandomPlayer<int> {
protected:
    vector<int> available_numbers;
public:
    Game5_RandomPlayer(int symbol, vector<int> numbers) ;
    void getmove(int& x,int& y);

};


#endif
