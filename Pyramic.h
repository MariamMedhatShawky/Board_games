
#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Pyramic_Board:public Board<T> {
public:
    Pyramic_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Pyramic_Player : public Player<T> {
public:
    Pyramic_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Pyramic_Random_Player : public RandomPlayer<T>{
public:
    Pyramic_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};




// IMPLEMENTATION



// Constructor for Pyramic_Board
template <typename T>
Pyramic_Board<T>::Pyramic_Board() {
    this->rows = 3; // The pyramid has 3 rows.
    this->columns = 5; // The widest row has 5 columns.
    
    // Dynamically allocate a 2D array where each row has a variable length
    this->board = new char*[this->rows];
    
    for (int i = 0; i < this->rows; i++) {
        // Calculate the number of columns for the current row
         int rowLength = 1 + 2 * i; // 1 for row 0, 3 for row 1, 5 for row 2
        this->board[i] = new char[rowLength];
        
        // Initialize all cells to 0 (empty)
        for (int j = 0; j < rowLength; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0; // Initialize the number of moves to 0
}

template <typename T>
bool Pyramic_Board<T>::update_board(int x, int y, T mark) {
    // Validate row index
    if (x < 0 || x >= this->rows) {
        return false; // Invalid row
    }

    // Determine valid column range for the given row
    int minColumn = 2 - x;  // Minimum column index for this row
    int maxColumn = 2 + x;  // Maximum column index for this row

    if (y < minColumn || y > maxColumn) {
        return false; // Invalid column
    }

    int boardIndex = y - minColumn; // Translate to valid index for the internal row array
    if (this->board[x][boardIndex] == 0 || mark == 0) {
        if (mark == 0) {
            this->n_moves--; // Clear the cell
            this->board[x][boardIndex] = 0;
        } else {
            this->n_moves++; // Place the mark
            this->board[x][boardIndex] = toupper(mark);
        }
        return true;
    }

    return false; // Cell is already occupied
}


template <typename T>
void Pyramic_Board<T>::display_board() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < this->rows; i++) {
        int minColumn = 2 - i; // Start of the valid cells
        int maxColumn = 2 + i; // End of the valid cells

        // Add leading spaces for alignment
        int leadingSpaces = 2 - i;
        for (int s = 0; s < leadingSpaces; ++s) {
            cout << "     "; // Adjust to match cell width
        }

        // Display valid cells in the current row
        for (int j = minColumn; j <= maxColumn; ++j) {
            int boardIndex = j - minColumn; // Translate to internal row index

            // Set cell content width to 5 characters for alignment
            if (this->board[i][boardIndex] == 0) {
                cout << "[" << i << "," << j << "]";
            } else {
                cout << "  " << this->board[i][boardIndex] << "  ";
            }
        }

        cout << endl; // Move to the next row
    }
}


template <typename T>
bool Pyramic_Board<T>::is_win() {
    // Check horizontal wins
    for (int i = 0; i < this->rows; i++) {
        int rowLength = 1 + 2 * i; // Calculate the number of cells in the current row
        for (int j = 0; j <= rowLength - 3; j++) { // Check for 3 consecutive marks
            if (this->board[i][j] == this->board[i][j + 1] && 
                this->board[i][j + 1] == this->board[i][j + 2] && 
                this->board[i][j] != 0) {
                return true;
            }
        }
    }

    // Check vertical wins
    for (int i = 0; i < this->rows - 2; i++) { // Only go up to the 3rd-to-last row
        int currentRowLength = 1 + 2 * i;
        int nextRowLength = 1 + 2 * (i + 1);
        int afterNextRowLength = 1 + 2 * (i + 2);

        for (int j = 0; j < currentRowLength; j++) {
            // Ensure indices align correctly for the pyramid structure
            if (j < nextRowLength && j < afterNextRowLength) {
                if (this->board[i][j] == this->board[i + 1][j] && 
                    this->board[i + 1][j] == this->board[i + 2][j] && 
                    this->board[i][j] != 0) {
                    return true;
                }
            }
        }
    }

    // Check diagonal wins (left-to-right and right-to-left)
    for (int i = 0; i < this->rows - 2; i++) {
        int currentRowLength = 1 + 2 * i;
        int nextRowLength = 1 + 2 * (i + 1);
        int afterNextRowLength = 1 + 2 * (i + 2);

        for (int j = 0; j < currentRowLength; j++) {
            // Left-to-right diagonal (\)
            if (j < nextRowLength - 1 && j < afterNextRowLength - 2) {
                if (this->board[i][j] == this->board[i + 1][j + 1] && 
                    this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && 
                    this->board[i][j] != 0) {
                    return true;
                }
            }

            // Right-to-left diagonal (/)
            if (j > 0 && j - 1 < nextRowLength && j - 2 < afterNextRowLength) {
                if (this->board[i][j] == this->board[i + 1][j - 1] && 
                    this->board[i + 1][j - 1] == this->board[i + 2][j - 2] && 
                    this->board[i][j] != 0) {
                    return true;
                }
            }
        }
    }

    return false; // No winner found
}



// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramic_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Pyramic_Player
template <typename T>
Pyramic_Player<T>::Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramic_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Pyramic_Random_Player
template <typename T>
Pyramic_Random_Player<T>::Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;  // Number of rows in the pyramid
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Get a random move for the pyramid XO game
template <typename T>
void Pyramic_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random row (0, 1, or 2)

    // Determine the valid column range for the chosen row
    int minColumn = 2 - x;
    int maxColumn = 2 + x;

    // Generate a random column within the valid range
    y = rand() % (maxColumn - minColumn + 1) + minColumn;
}





#endif //PYRAMID_X_O_H


