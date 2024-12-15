#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Word.h"

using namespace std;

int main() {
    
    int choice;
    Player<char>* players[2];
    Board<char>* B = new Word_Board<char>();
    dynamic_cast<Word_Board<char>*>(B)->readFile();

    string player1Name, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name \"NO SPACES\": ";
    cin >> player1Name;
    while (true) {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        if (!(cin >> choice)) { // Validate numeric input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            players[0] = new Word_Player<char>(player1Name, '\0');  // Symbol will be dynamically set
            break;
        } else if (choice == 2) {
            players[0] = new Word_Random_Player<char>('\0');
            break;
        } else {
            cout << "Invalid choice for Player 1. Please try again.\n";
        }
    }

    // Set up player 2
    cout << "Enter Player 2 name \"NO SPACES\": ";
    cin >> player2Name;
    while (true) {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        if (!(cin >> choice)) { // Validate numeric input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            players[1] = new Word_Player<char>(player2Name, '\0');  // Symbol will be dynamically set
            break;
        } else if (choice == 2) {
            players[1] = new Word_Random_Player<char>('\0');
            break;
        } else {
            cout << "Invalid choice for Player 2. Please try again.\n";
        }
    }

     // Create the game manager and run the game
    GameManager<char> word_tic_tac_toe(B, players);
    word_tic_tac_toe.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



