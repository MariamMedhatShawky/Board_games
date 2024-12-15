#include <iostream>
#include "BoardGame_Classes.h"
#include "pyramic.h"


using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Board<char>* B = new Pyramic_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name \"NO SPACES\": ";
    cin >> player1Name;
    while(true){
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    if (!(cin >> choice)) { // Validate numeric input
            cout << "Invalid input. Please enter a number.\n";
            continue;
    }
    if (choice == 1) {
            players[0] = new Pyramic_Player<char>(player1Name, 'X');
            break;
        } else if (choice == 2) {
            players[0] = new Pyramic_Random_Player<char>('X');
            break;
        } else {
            cout << "Invalid choice for Player 1. Please try again.\n";
        }
    }

    // Set up player 2
    cout << "Enter Player 2 name \"NO SPACES\": ";
    cin >> player2Name;
    while(true){
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
        if (!(cin >> choice)) { // Validate numeric input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            players[1] = new Pyramic_Player<char>(player2Name, 'O');
            break;
        } else if (choice == 2) {
            players[1] = new Pyramic_Random_Player<char>('O');
            break;
        } else {
            cout << "Invalid choice for Player 2. Please try again.\n";
        }
    }

    // Create the game manager and run the game
    GameManager<char> pyramic_tic_tac_toe_game(B, players);
    pyramic_tic_tac_toe_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



