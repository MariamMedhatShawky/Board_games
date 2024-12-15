#include <iostream>
#include <string>
#include "BoardGame_Classes.h"
#include "XO.h"

using namespace std;

int main() {
    int choice, choice3;
    char choice2;

    // Initialize the players array
    Player<char>* players[2] = {nullptr, nullptr};

    string playerXName, player2Name;

    // Input for Player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;

    // Player 1 symbol selection
    while (true) {
        cout << "Choose the symbol for Player 1 ('X'/'O')\n";
        cin >> choice2;

        if (choice2 == 'x' || choice2 == 'X' || choice2 == 'o' || choice2 == 'O') {
            break;
        } else {
            cout << "Invalid symbol. Please choose 'X' or 'O'.\n";
        }
    }

    // Player 1 type selection (Human or Random Computer)
    while (true) {
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";

        cin >> choice;

        // Check for valid input
        if (cin.fail()) {
            cin.clear();  // Clear the error flag
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }

        if (choice == 1 || choice == 2) {
            if (choice == 1) {
                players[0] = new PlayerXO<char>(playerXName, toupper(choice2), nullptr);  // Human Player with Player1's symbol
            } else {
                players[0] = new RandomPlayerXO<char>(toupper(choice2), nullptr);  // Random Player with Player1's symbol
            }
            break;
        } else {
            cout << "Invalid choice. Please choose 1 or 2.\n";
        }
    }

    cout << playerXName << ", you have the symbol " << choice2 << ".\n";

    // Determine Player 2's symbol
    char player2Symbol = (toupper(choice2) == 'X') ? 'O' : 'X';

    // Input for Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;

    cout << player2Name << ", you have the symbol " << player2Symbol << ".\n";
    cout << "=======================\n";

    // Player 2 type selection (Human or Random Computer)
    if (choice == 2) {  // If Player 1 is Random, Player 2 must be Human
        cout << "Since Player 1 is Random, Player 2 must be Human.\n";
        players[1] = new PlayerXO<char>(player2Name, player2Symbol, nullptr);  // Player 2 must be Human
    } else {
        while (true) {
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice3;

            // Check for valid input
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cout << "Invalid input. Please enter 1 or 2.\n";
                continue;
            }

            if (choice3 == 1 || choice3 == 2) {
                if (choice3 == 1) {
                    players[1] = new PlayerXO<char>(player2Name, player2Symbol, nullptr);  // Human Player
                } else {
                    players[1] = new RandomPlayerXO<char>(player2Symbol, nullptr);  // Random Player
                }
                break;
            } else {
                cout << "Invalid choice. Please choose 1 or 2.\n";
            }
        }
    }

    // Initialize the board for the game with players array
    TicTacToe<char>* B = new TicTacToe<char>(players);

    // Set the board pointer in both players (so they know about the game board)
    players[0]->setBoard(B);
    players[1]->setBoard(B);

    // Initialize the GameManager with the board and the players
    GameManager<char> game(B, players);

    // Run the game (game loop)
    game.run();

    // Clean up dynamically allocated memory
    delete players[0];  // Delete Player 1 object
    delete players[1];  // Delete Player 2 object
    delete B;  // Delete the board

    return 0;
}
