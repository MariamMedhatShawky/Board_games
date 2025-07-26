# include<iostream>
#include"BoardGame_classes.h"
using namespace std;

template<typename T>
class Misere : public Board<char> {
public:

    Misere() {
        n_moves = 0;
        rows = 3;
        columns = 3;
        board = new char*[rows];  // Create an array of pointers for rows
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];  // Allocate each row dynamically
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '-';  // Initialize each cell with '-'
            }
        }
    }

    ~Misere(){
        for (int i = 0; i < rows; ++i){
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns) {
            if (board[x][y] == '-') {
                board[x][y] = symbol;
                ++n_moves;
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
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool is_win() override{
        for (int i = 0; i < rows ;++i){
            for (int j = 0; j < columns; ++j){
                if ( j == 1 ){
                    if ( board[i][j] ==  board[i][j - 1] &&  board[i][j] == board[i][j + 1]  && board[i][j] != '-'){
                        return true;
                    }
                }

                if ( i == 1 ){
                    if (board[i][j] ==  board[i + 1][j] && board[i - 1][j] == board[i][j] && board[i][j] != '-'){
                        return true;
                    }

                }

                if ( i == 1 && j == 1){
                    if ( board[i][j] != '-' && board[i + 1][j + 1] ==  board[i][j]  && board[i - 1][j - 1] == board[i][j] ){
                        return true;
                    }
                    if ( board[i][j] != '-' && board[i][j] == board[i - 1][j + 1] &&  board[i + 1][j - 1] == board[i][j]){
                        return true;

                    }

                }

            }
        }
        return false;

    }


    bool is_draw() override{
        if (n_moves == 9 && !is_win()){
            return true;
        }
        return false;
    }

    bool game_is_over() override{
        if (is_draw() || is_win()){
            return true;
        }
        return false;
    }
};

template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol, Board<T>* board) : Player<T>(name, symbol) {
        this->boardPtr = board;
    }

    void getmove(int& x, int& y) override {
        cout << "Enter move (row column) separated by a space.\n: ";
        cin >> x >> y;
    }
};

template <typename T>
class Random_Misere_Player : public Misere_Player<T> {
public:
    Random_Misere_Player(T symbol, Board<T>* board) : Misere_Player<T>("Random player",symbol, board) {
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }

    void getmove(int& x, int& y) override {

        x = rand() % 3;
        y = rand() % 3;

    }
};

