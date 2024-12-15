#ifndef _GAME9_H
#define _GAME9_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SUS_Board : public Board<T> {
private:
    int scores[2] = {0, 0}; // Scores for two players

public:
    SUS_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int get_score(int player_index); // Get score for a player
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int &x, int &y);
};




// IMPLEMENTATION



// Constructor for SUS_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update the board with a move
// Return true if the move is valid, false otherwise
template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T symbol) {
    // Validate move coordinates and check if the cell is empty
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false; // Invalid move
    }

    // Place the player's symbol on the board
    this->board[x][y] = symbol;

    // Update the number of moves made
    this->n_moves++;

    // Identify the player index based on the symbol
    int player_index = (symbol == 'S') ? 0 : 1;

    // Check the row and column affected by the move
    string row = string(1, this->board[x][0]) + this->board[x][1] + this->board[x][2];
    if (row == "SUS") scores[player_index]++;

    string col = string(1, this->board[0][y]) + this->board[1][y] + this->board[2][y];
    if (col == "SUS") scores[player_index]++;

    // Check the diagonals if the move was on a diagonal
    if (x == y) { // Move is on the main diagonal
        string diag_a = string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2];
        if (diag_a == "SUS") scores[player_index]++;
    }
    if (x + y == 2) { // Move is on the anti-diagonal
        string diag_b = string(1, this->board[2][0]) + this->board[1][1] + this->board[0][2];
        if (diag_b == "SUS") scores[player_index]++;
    }

    return true; // Move was valid and board updated
}





// Display the board
// Show rows and columns with coordinates
template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 'S' && this->board[i][j] != 'U') {
                cout << "[" << i << "," << j << "]";
            } else {
                cout << "  " << this->board[i][j] << "  ";
            }
            cout << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


// No longer needed as we count scores instead of immediate win
template <typename T>
bool SUS_Board<T>::is_win() {
    return false;
}



// Check if the board is full
// Return true if no more moves are possible
template <typename T>
bool SUS_Board<T>::is_draw() {
    return this->n_moves == 9;
}

// Check if the game is over
template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_draw();
}

// Get the score of a specific player
template <typename T>
int SUS_Board<T>::get_score(int player_index) {
    return scores[player_index];
}

//--------------------------------------

// SUS_Player constructor
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get the next move from the player
template <typename T>
void SUS_Player<T>::getmove(int &x, int &y) {
    cout << "\n" << this->name << ", enter your move (row column): ";
    cin >> x >> y;
}

// SUS_Random_Player constructor
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

// Get the next move for the random player
template <typename T>
void SUS_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % 3;
    y = rand() % 3;
}



#endif //_GAME9_H
