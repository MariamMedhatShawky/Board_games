#ifndef _WORD_H
#define _WORD_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Word_Board:public Board<T> {
private:
    vector<string> dic;
public:
    Word_Board ();
    void readFile();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};




// IMPLEMENTATION



// Constructor for Word_Board
template <typename T>
Word_Board<T>::Word_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
void Word_Board<T>::readFile(){
    ifstream file("dic.txt");
    if (!(file.is_open())){
        cout << "Failed to open dic file!!\n"; 
    }
    string line;
    while (getline(file, line)) {
        dic.push_back(line);
    }
    file.close();
}

template <typename T>
bool Word_Board<T>::update_board(int x, int y, T letter) {
    // Validate move coordinates and check if the cell is empty
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;  // Invalid move 
    }

    // Place the letter on the board
    this->board[x][y] = toupper(letter);

    // Update the number of moves made
    this->n_moves++;

    // Return true after a valid update, allowing the game to continue
    return true;
}


// Display the board and the pieces on it
template <typename T>
void Word_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


template <typename T>
bool Word_Board<T>::is_win() {
    // Check all the possible patterns (horizontal, vertical, and diagonal)
    for (auto word : dic) {
        // Check horizontal rows
        
        for (int i = 0; i < 3; ++i) {
            string row1 = string(1, this->board[i][0]) + this->board[i][1] + this->board[i][2];
            if (row1 == word) return true;
        }
        for (int i = 0; i < 3; ++i) {
            string row2 = string(1, this->board[i][2]) + this->board[i][1] + this->board[i][0];
            if (row2 == word) return true;
        }


        // Check vertical columns
        for (int i = 0; i < 3; ++i) {
            string col1 = string(1, this->board[0][i]) + this->board[1][i] + this->board[2][i];
            if (col1 == word) return true;
        }
        for (int i = 0; i < 3; ++i) {
            string col2 = string(1, this->board[2][i]) + this->board[1][i] + this->board[0][i];
            if (col2 == word) return true;
        }


        // Check diagonals

        string diag_a = string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2];
        if (diag_a == word) return true;
                
        string diag_b = string(1, this->board[2][2]) + this->board[1][1] + this->board[0][0];
        if (diag_b == word) return true;



        string diag_c = string(1, this->board[2][0]) + this->board[1][1] + this->board[0][2];
        if (diag_c == word) return true;

        string diag_d = string(1, this->board[0][2]) + this->board[1][1] + this->board[2][0];
        if (diag_d == word) return true;

    }
    return false;
}



// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Word_Player
template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    char letter;
    cout << "\n" << this->name << ", enter your move (row column letter): ";
    cin >> x >> y >> letter;

    // Validate input
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || !isalpha(letter)) {
        cout << "Invalid input. Please try again.\n";
        getmove(x, y);  // Retry for valid input
    } else {
        this->symbol = toupper(letter);  // Update the symbol with the new letter
    }
}


// Constructor for Word_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
    this->symbol = 'A' + (rand() % 26);  // Generate a random letter
    cout << this->name << " plays: (" << x << ", " << y << ") with letter '" << this->symbol << "'\n";
}




#endif //_WORD_H

