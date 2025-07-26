#include <iostream>
#include "BoardGame_Classes.h"
using namespace std;

int moves;

template<typename T>
class TicTacToe : public Board<char> {
public:
    TicTacToe() {
        this->n_moves = 0;
        this->rows = 5;
        this->columns = 5;
        this->board = new char*[this->rows];  // Create an array of pointers for rows
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];  // Allocate each row dynamically
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '-';  // Initialize each cell with '-'
            }
        }
    }

    ~TicTacToe() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, char sym) override {
        if (this->n_moves >= 24) {
            this->n_moves = 25;
            moves = this->n_moves;
            return true;
        }
        moves = this->n_moves;
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
            if (this->board[x][y] == '-') {
                this->board[x][y] = sym;
                ++this->n_moves;
                return true;
            } else {
                cout << "Invalid move, please choose an empty cell.\n";
                return false;
            }
        } else {
            cout << "Invalid move, please choose a valid cell within bounds.\n";
            return false;
        }
    }

    void display_board() override {
        cout << "----------\n";
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool is_win() override {
        if (this->n_moves >= 24) {
            int move = this->n_moves;
            int x_score = 0;
            int o_score = 0;
            int score = 0;


            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    char sym = this->board[i][j];
                    if (j == 1 || j == 2 || j == 3) {
                        if (this->board[i][j] == sym && this->board[i][j - 1] == sym && this->board[i][j + 1] == sym && this->board[i][j] != '-') {
                            ++score;
                            if (sym == 'X' || sym == 'x') {
                                x_score++;
                            } else {
                                o_score++;
                            }
                        }
                    }
                    if (i == 1 || i == 2 || i == 3){
                        if (this->board[i][j] == sym && this->board[i + 1][j] == sym && this->board[i - 1][j] == sym && this->board[i][j] != '-') {
                            ++score;
                            if (sym == 'X' || sym == 'x') {
                                x_score++;
                            } else {
                                o_score++;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    char sym = this->board[i][j];
                    if (i == 1 || i == 2 || i == 3){
                        if (j == 1 || j == 2 || j == 3) {
                            if (this->board[i][j] != '-' && this->board[i + 1][j + 1] == sym && this->board[i][j] == sym && this->board[i - 1][j - 1] == sym) {
                                ++score;
                                if (sym == 'X' || sym == 'x') {
                                    x_score++;
                                } else {
                                    o_score++;
                                }
                            }
                            if (this->board[i][j] != '-' && this->board[i][j] == sym && this->board[i - 1][j + 1] == sym && this->board[i + 1][j - 1] == sym) {
                                ++score;
                                if (sym == 'X' || sym == 'x') {
                                    x_score++;
                                } else {
                                    o_score++;
                                }
                            }
                        }
                    }
                }
            }

            cout << "Player with letter 'X' scored" << " " << x_score << " "<<",while player with letter 'O' scored"<<" " << o_score<< "."<<endl;

            if (this->n_moves == 24) {
                moves = this->n_moves;
                if (o_score > x_score) return true;
                return false;
            } else if (this->n_moves == 25) {
                moves = this->n_moves;
                if (x_score > o_score) return true;
                return false;
            }
        }
        return false;
    }

    bool is_draw() override {
        return this->n_moves == 25 && !is_win();
    }

    bool game_is_over() override {
        return this->n_moves == 25;
    }
};

template <typename T>
class PlayerXO : public Player<T> {
public:
    PlayerXO(std::string name, T symbol, Board<T>* board) : Player<T>(name, symbol) {
        this->boardPtr = board;
    }

    void getmove(int& x, int& y) override {
        cin >> x >> y;
    }
};

template <typename T>
class RandomPlayerXO : public RandomPlayer<T> {
public:
    RandomPlayerXO(T symbol, Board<T>* board) : RandomPlayer<T>(symbol) {
        this->boardPtr = board;
        this->name = "Random Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }

    void getmove(int& x, int& y) override {
        if (moves >= 24) return;
        x = rand() % 5;
        y = rand() % 5;
    }
};
