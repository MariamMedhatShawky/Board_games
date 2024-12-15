#include <bits/stdc++.h>
#include "game9.h"

using namespace std;


int main() {
    SUS_Board<char> board;
    SUS_Player<char> player1("Player 1", 'S');
    SUS_Player<char> player2("Player 2", 'U');

    int x, y;
    bool move_valid;

    cout << "Starting SUS Game!\n";
    board.display_board(); // Display the initial empty board

    while (!board.game_is_over()) {
        // Player 1 Move
        do {
            player1.getmove(x, y);
            move_valid = board.update_board(x, y, 'S');
            if (!move_valid) cout << "Invalid move, try again.\n";
        }while (!move_valid);
        board.display_board();

        if (board.game_is_over()) break; // Check for game over after Player 1

        // Player 2 Move
        do {
            player2.getmove(x, y);
            move_valid = board.update_board(x, y, 'U');
            if (!move_valid) cout << "Invalid move, try again.\n";
        } while (!move_valid);
        board.display_board();

        // Check if the game is over
    }

    cout << "\nGame Over!\n";
    cout << "Player 1 Score (S): " << board.get_score(0) << endl;
    cout << "Player 2 Score (U): " << board.get_score(1) << endl;
    if (board.get_score(0) > board.get_score(1)){
        cout << "Player 1 wins";
    }
    else if (board.get_score(0) < board.get_score(1)){
        cout << "Player 2 wins";
    }
    else cout << "Draw!";

    return 0;
}
