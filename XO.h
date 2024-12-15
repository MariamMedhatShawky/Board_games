#include <iostream>
#include "BoardGame_Classes.h"
using namespace std;

template<typename T>
class TicTacToe : public Board<char> {
public:
    Player<char>* players[2];
    bool flag = false;
    TicTacToe(Player<char>* players[]) {
        n_moves = 0;
        rows = 5;
        columns = 5;
        this->players[0] = players[0]; 
        this->players[1] = players[1];
        board = new char*[rows];  // Create an array of pointers for rows
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];  // Allocate each row dynamically
            for (int j = 0; j < columns; ++j) {
                board[i][j] = '-';  // Initialize each cell with '-'
            }
        }
    }

    ~TicTacToe() { 
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
        cout << "----------\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
    }

    int calculate_winning_patterns(char sym){
        int score = 0;

        for (int i = 0; i < rows ;++i){
            for (int j = 0; j < columns; ++j){
                if ( j == 1 || j == 2 || j == 3){ 
                    if ( board[i][j] == sym && board[i][j - 1] == sym && board[i][j + 1] == sym && board[i][j] != '-'){
                        ++score; 
                    }
                }
                if ( i == 1 || i == 2 || i == 3){ 
                    if (board[i][j] == sym && board[i + 1][j] == sym && board[i - 1][j] == sym && board[i][j] != '-'){
                        ++score; 
                    } 
                } 
            } 
        } 
        for (int i = 0; i < rows ;++i){ 
            for (int j = 0; j < columns ; ++j){ 
                if ( i == 1 || i == 2 || i == 3 ){ 
                    if (j == 1 || j == 2 || j == 3){ 
                        if ( board[i][j] != '-' && board[i + 1][j + 1] == sym && board[i][j] == sym && board[i - 1][j - 1] == sym){ 
                            ++score; 
                        } 
                        if ( board[i][j] != '-' && board[i][j] == sym && board[i - 1][j + 1] == sym && board[i + 1][j - 1] == sym){ 
                            ++score; 
                        } 
                    } 
                } 
            } 
        }
        return score;

    }

    bool is_win()override{
        
        if (game_is_over()){
            
            int player1score = calculate_winning_patterns(players[0]->getsymbol()); 
            int player2score = calculate_winning_patterns(players[1]->getsymbol());

            if (player1score > player2score) { 
                cout << "Game ended. Player with letter"<< " " <<players[0]->getsymbol()<<" "<<"scored"<<" "<< player1score<<" "<<",while player with the letter"<<" "<<players[1]->getsymbol()<<" "<<"scored" <<" "<< player2score<<".\n";
                cout << players[0]
                ->getname() << " wins\n";
                flag = true;
                return false;
            }
            else if (player2score > player1score) {
                cout << "Game ended. Player with letter"<< " " <<players[0]->getsymbol()<<" "<<"scored"<<" "<< player1score<<" "<<",while player with the letter"<<" "<<players[1]->getsymbol()<<" "<<"scored" <<" "<< player2score<<".\n";
                cout << players[1]
                ->getname() << " wins\n";
                flag = true;
                return false;
            }
        
        }
    return false;
    }

    bool is_draw() override {
        return n_moves == 25 && !flag;
    }

    bool game_is_over() override {
        return n_moves == 25;
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
        
        x = rand() % 5;
        y = rand() % 5;
        
    }
};
