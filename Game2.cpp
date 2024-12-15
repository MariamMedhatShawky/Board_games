#include "Game2.h"

Game2_Board::Game2_Board() {
    this->rows = 7;
    this->columns = 6;
    this->board = new char *[7];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


bool Game2_Board::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0 &&
         (x == 6 || board[x + 1][y] == 'O' || board[x + 1][y] == 'X')) {
        this->board[x][y] = toupper(symbol);
        this->n_moves ++;
        return true;
    }
    return false;
}


void Game2_Board::display_board() {
    cout << "    0 1 2 3 4 5 " << endl;
    for (int i = 0; i < rows; ++i) {
        cout << i <<" | ";
        for (int j = 0; j < columns; ++j) {
            cout << (board[i][j] ? board[i][j] : '.') << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << "  ";
    for (int col = 0; col < columns; ++col) {
        cout << "--";
    }
    cout << "-" << endl;
}


bool Game2_Board::is_win() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col <= columns - 4; ++col) {
            if (board[row][col] == board[row][col + 1] &&
            board[row][col] == board[row][col + 2] &&
            board[row][col] == board[row][col + 3] &&
            board[row][col] != 0 ) {
                return true;
            }
        }
    }

    // Check vertical win
    for (int col = 0; col < columns; ++col) {
        for (int row = 0; row <= rows - 4; ++row) {
            if (board[row][col] == board[row + 1][col] &&
            board[row][col] == board[row + 2][col] &&
            board[row][col] == board[row + 3][col] &&
            board[row][col] != 0 ) {
                return true;
            }
        }
    }

    // Check diagonal win (top-left to bottom-right ↘)
    for (int row = 0; row <= rows - 4; ++row) {
        for (int col = 0; col <= columns - 4; ++col) {
            if (board[row][col] == board[row + 1][col + 1] &&
            board[row][col] == board[row + 2][col + 2] &&
            board[row][col]== board[row + 3][col + 3] &&
            board[row][col] != 0 ) {
                return true;
            }
        }
    }

    // Check diagonal win (bottom-left to top-right ↗)
    for (int row = 3; row < rows; ++row) {
        for (int col = 0; col <= columns - 4; ++col) {
            if (board[row][col] == board[row - 1][col + 1] &&
            board[row][col] == board[row - 2][col + 2] &&
            board[row][col] == board[row - 3][col + 3] &&
            board[row][col] != 0 ) {
                return true;
            }
        }
    }

    return false;

}


bool Game2_Board::is_draw() {
    if (n_moves >= 42 && !is_win()){
        return true;
    }
    return false;
}


bool Game2_Board::game_is_over() {
   return is_win() || is_draw();
}

Game2_Board::~Game2_Board() {
    for (int i = 0; i < 3; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

int Game2_Board::minimax(int &x, int &y, bool is_max, bool is_finished) {
    int res, score, min = 100, max = -100, fx = -1, fy = -1;

    // Evaluate the game state
    if (is_win() && is_max) res = 2;
    else if (is_win() && !is_max) res = -2;
    else if (is_draw()) res = 0;
    else res = 1;

    // Base case: if the game is over, return the evaluation
    if (res != 1) {
        return res;
    }

    // Iterate over valid moves
    for (int col = 0; col < columns; ++col) {
        for (int row = rows - 1; row >= 0; --row) { // Start from the bottom of the column
            if (board[row][col] == 0) {
                if (is_max) {
                    // Simulate the move for the maximizing player
                    board[row][col] = 'O';
                    score = minimax(x, y, false, false);
                    board[row][col] = 0; // Undo the move
                    if (score > max) {
                        max = score;
                        fx = row;
                        fy = col;
                    }
                } else {
                    // Simulate the move for the minimizing player
                    board[row][col] = 'X';
                    score = minimax(x, y, true, false);
                    board[row][col] = 0; // Undo the move
                    if (score < min) {
                        min = score;
                        fx = row;
                        fy = col;
                    }
                }
                break; // Stop checking this column after finding the first empty cell
            }
        }
    }

    // Update the best move if this is the final decision
    if (is_finished) {
        x = fx;
        y = fy;
    }

    return is_max ? max : min;
}

Game2_Player::Game2_Player(string name, char symbol) : Player(name, symbol) {}


void Game2_Player::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x and y separated by spaces: ";
    cin >> x >> y;
}


Game2_RandomPlayer::Game2_RandomPlayer(char symbol) : RandomPlayer(symbol) {
    this->dimension = 7;
    this->dimension2 = 6;
    this->name = "Random Computer Player";
}


void Game2_RandomPlayer::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension2;

}

Game2_AIPlayer::Game2_AIPlayer(char symbol, Game2_Board *board) :Player(symbol), board(board) {}

void Game2_AIPlayer::getmove(int &x, int &y) {
    board->minimax(x, y, true, true);


}
