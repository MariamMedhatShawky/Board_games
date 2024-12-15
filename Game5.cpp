#include "Game5.h"

Game5_Board::Game5_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new int *[3];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[3];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = -100;
        }
    }
    this->n_moves = 0;
}


bool Game5_Board::update_board(int x, int y, int symbol) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || this->board[x][y] != -100) {
        return true;
    }
    this->board[x][y] = symbol;
    if(symbol != -100) {
        n_moves++;
    }
    return false;
}


void Game5_Board::display_board() {
    cout << "     0 1 2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " | " << " ";
        for (int j = 0; j < 3; j++) {
            if (this->board[i][j] == -100) {
                cout << '-';
            }
            else{
                cout << this->board[i][j];
            }
            cout << " ";
        }
        cout << " |";
        cout << "\n";
    }

}


bool Game5_Board::is_win() {

    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != -100 && this->board[i][1] !=-100 && this->board[i][2] !=-100) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != -100 && this->board[1][i] !=-100 && this->board[2][i] !=-100)) {
            return true;
        }
    }

    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != -100 && this->board[1][1] !=-100 && this->board[2][2] !=-100) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] != -100 && this->board[1][1] !=-100 && this->board[2][0] !=-100)) {
        return true;
    }
    return false;
}


bool Game5_Board::is_draw() {
    if (n_moves > 9 && !is_win()){
        return true;
    }
    return false;
}


bool Game5_Board::game_is_over() {
    return is_win() || is_draw();
}


Game5_Board::~Game5_Board() {
    for (int i = 0; i < 3; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}


Game5_Player::Game5_Player(string name, int symbol, vector<int> numbers) : Player<int>(name, symbol) {
    this->available_numbers = numbers;
}


void Game5_Player::getmove(int &x, int &y) {
    cout << this->getname() << "'s turn. Available numbers: ";
    for (int num : available_numbers) cout << num << " ";
    cout << "\nEnter row and column (0-2): ";

    while (true) {
        cin >> x >> y;

        // Prompt for a valid number if the board update fails
        if (boardPtr->update_board(x, y, -100)) {
            cout << "Indices is not valid, please try another." << endl;
            continue;
        }
        break;
    }

    cout << "Enter a number to place: ";
    while (true) {
        cin >> symbol;
        // Validate the number
        if (find(available_numbers.begin(), available_numbers.end(), symbol) == available_numbers.end()) {
            cout << "Invalid number. Choose from available numbers: ";
            continue;
        }
        // Place the number on the board
        if (!boardPtr->update_board(x, y, symbol)) {
            available_numbers.erase(find(available_numbers.begin(), available_numbers.end(), symbol));
            break;
        }
        else {
            continue;
        }
    }
}


Game5_RandomPlayer::Game5_RandomPlayer(int symbol, vector<int> numbers) : RandomPlayer(symbol) {
    this->available_numbers = numbers;
}


void Game5_RandomPlayer::getmove(int &x, int &y) {
    while (true) {
        x = rand() % 3;
        y = rand() % 3;

        // Prompt for a valid number if the board update fails
        if (boardPtr->update_board(x, y, -100)) {
            continue;
        }
        break;
    }
    int num;

    while (true) {
        num = rand() % 9;
        // Validate the number
        if (find(available_numbers.begin(), available_numbers.end(), num) == available_numbers.end()) {
            continue;
        }
        // Place the number on the board
        if (!boardPtr->update_board(x, y, num)) {
            cout << "\nComputer's turn: " <<endl;
            available_numbers.erase(find(available_numbers.begin(), available_numbers.end(), num));
            break;
        }
        else
        {
            continue;
        }
    }

    }


