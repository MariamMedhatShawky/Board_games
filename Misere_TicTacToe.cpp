#include <iostream>
#include <string>
#include "BoardGame_classes.h"
#include "Misere_TicTacToe.h"
using namespace std;

int main() {
    int choice, choice3;


    // Initialize the players array
    Player<char>* players[2] = {nullptr, nullptr};

    string playerXName, player2Name;

    // Input for Player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;




    // Player 1 type selection (Human or Random Computer)

    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";

    cin >> choice;


    cout << playerXName << ", you have the symbol " << 'X' << ".\n";

    // Input for Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;

    cout << player2Name << ", you have the symbol " << 'O' << ".\n";
    cout << "=======================\n";

    // Player 2 type selection (Human or Random Computer)

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice3;



    if (choice == 1) {
        players[0] = new Misere_Player<char>(player2Name, 'X', nullptr);  // Human Player with Player1's symbol
    }
    else {
        players[0] = new Random_Misere_Player<char>('X', nullptr);  // Random Player with Player1's symbol
    }
    if (choice3 == 1) {
        players[1] = new Misere_Player<char>(playerXName, 'O', nullptr);  // Human Player
    } else {
        players[1] = new Random_Misere_Player<char>('O', nullptr);  // Random Player
    }





    // Initialize the board for the game with players array
    Misere<char>* B = new Misere<char>();


    // Initialize the GameManager with the board and the players
    GameManager<char> game(B, players);

    // Run the game (game loop)
    game.run();

    // Clean up dynamically allocated memory
    delete players[0];  // Delete Player 1 object
    delete players[1];  // Delete Player 2 object
    delete B;  // Delete the board
    return;

    return 0;

