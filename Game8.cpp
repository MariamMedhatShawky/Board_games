#include "Game8.h"
#include <bits/stdc++.h>
using namespace std;


Game8_MiniBoard::Game8_MiniBoard() {
    this->board = new char *[3];
    for (int i = 0; i < 3; i++) {
        this->board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}


bool Game8_MiniBoard::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
        this->board[x][y] = toupper(symbol);
        this->n_moves ++;
        return true;
    }
    return false;
}

void Game8_MiniBoard::display_board() {}

//to get the symbol from miniboard
char Game8_MiniBoard::get_symbol(int x, int y) {
    return board[x][y];
}

bool Game8_MiniBoard::is_win() {
    char symbol = ' ';

    // Check rows for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            symbol = board[i][0];
        }
    }

    // Check columns for a win
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            symbol = board[0][i];
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        symbol = board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        symbol = board[0][2];
    }

    // If there's a winner, fill the entire board with the winning symbol
    if (symbol != ' ') {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = symbol;
            }
        }
        return true;
    }
    return false;
}



bool Game8_MiniBoard::is_draw() {
    if(n_moves == 9 && !is_win() ) return true;
    return false;
}


bool Game8_MiniBoard::game_is_over() {
    return is_win()||is_draw();
}


// the main board
Game8_MainBoard::Game8_MainBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            boards[i][j] = new Game8_MiniBoard();
        }
    }
}

Game8_MainBoard::~Game8_MainBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            delete boards[i][j];
        }
    }
}

bool Game8_MainBoard::update_board(int x, int y, char symbol) {
    // Row and column in the main 3x3 grid
    int board_x = x / 3;
    int board_y = y / 3;

    // Update the mini-board
    return boards[board_x][board_y]->update_board(x % 3, y % 3, symbol);
}

void Game8_MainBoard::display_board() {
    cout << "\n9x9 Board:" << endl;

    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            int board_x = i / 3;
            int board_y = j / 3;

            // Print the current symbol (X/O) in the big grid corresponding to the mini-board
            char symbol = boards[board_x][board_y]->get_symbol(i % 3, j % 3);

            if (symbol == ' ') {
                cout << "(" << i << "," << j << ") ";
            }
            else {

                cout << "  " << symbol << "   ";
            }

            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;

        if ((i + 1) % 3 == 0) {
            cout << "-------------------------------------------------------------" << endl;
        }
    }
}

bool Game8_MainBoard::is_win() {
    for (int i = 0; i < 3; ++i) {
        if (boards[i][0]->is_win() && boards[i][1]->is_win() && boards[i][2]->is_win() &&
            boards[i][0]->get_symbol(0, 0) == boards[i][1]->get_symbol(0, 0) && boards[i][1]->get_symbol(0, 0) == boards[i][2]->get_symbol(0, 0)) {
            return true;
        }
        if (boards[0][i]->is_win() && boards[1][i]->is_win() && boards[2][i]->is_win() &&
            boards[0][i]->get_symbol(0, 0) == boards[1][i]->get_symbol(0, 0) && boards[1][i]->get_symbol(0, 0) == boards[2][i]->get_symbol(0, 0)) {
            return true;
        }
        if (boards[0][0]->is_win() && boards[1][1]->is_win() && boards[2][2]->is_win() &&
            boards[0][0]->get_symbol(0, 0) == boards[1][1]->get_symbol(0, 0) && boards[1][1]->get_symbol(0, 0) == boards[2][2]->get_symbol(0, 0)) {
            return true;
        }
        if(boards[0][2]->is_win() && boards[1][1]->is_win() && boards[2][0]->is_win() &&
           boards[0][2]->get_symbol(0, 0) == boards[1][1]->get_symbol(0, 0) && boards[1][1]->get_symbol(0, 0) == boards[2][0]->get_symbol(0, 0)) {
            return true;
        }
    }
    return false;
}

bool Game8_MainBoard::is_draw() {
    // Check if all boards are filled and there's no winner
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!boards[i][j]->is_draw()) {
                return false;
            }
        }
    }
    return true;
}

bool Game8_MainBoard::game_is_over() {
    return is_win() || is_draw();
}


Game8_Player::Game8_Player(string name, char symbol) : Player(name, symbol) {}

void Game8_Player::getmove(int &x, int &y) {
    cout << name << ", Enter your move (row and column): ";
    cin >> x >> y;
}

Game8_RandomPlayer::Game8_RandomPlayer(char symbol) : RandomPlayer<char>(symbol) {

}

void Game8_RandomPlayer::getmove(int &x, int &y) {
    x = rand() % 3;
    y = rand() % 3;
    cout << "Computer chose: " << x << ", " << y << endl;
}

