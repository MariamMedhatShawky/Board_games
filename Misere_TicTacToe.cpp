#include <iostream>
#include <string>
#include "BoardGame_classes.h"
#include "Misere_TicTacToe.h"
using namespace std;

int main() {
    int choice;
    char choice2;
    // Initialize the board for the game
    Player<char>* players[2];

    // Player names
    string player1Name, player2Name; 

    // Initialize players to nullptr
    Player<char>* player1 = nullptr;
    Player<char>* player2 = nullptr;

    // Array of players for the GameManager
    Player<char>* playersArray[2] = {player1, player2};

    cout << "Enter Player1 name: ";
    cin >> player1Name;

    cout << "Choose the symbol for player1 ('X'/'O')\n";
    cin >> choice2;

    cout << "Choose Player1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1 && (choice2 == 'X' || choice2 == 'x')) {
        playersArray[0] = new Misere_Player<char>(player1Name, 'X', nullptr);
    } else if (choice == 1 && (choice2 == 'O' || choice2 == 'o')) {
        playersArray[0] = new Misere_Player<char>(player1Name, 'O', nullptr);
    } else if (choice == 2 && (choice2 == 'X' || choice2 == 'x')) {
        playersArray[0] = new Random_Misere_Player<char>('X', nullptr);
    } else if (choice == 2 && (choice2 == 'O' || choice2 == 'o')) {
        playersArray[0] = new Random_Misere_Player<char>('O', nullptr);
    }


    cout << player1Name << " " << "You have the symbol" << " " << choice2 << std::endl;

    // Determine Player 2's symbol
    char player2Symbol = (choice2 == 'X' || choice2 == 'x') ? 'O' : 'X';

    cout << "Enter Player2 name: ";
    cin >> player2Name;

    cout << player2Name << " " << "You have the symbol " << player2Symbol << "\n";
    cout << "=======================" << "\n";

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        playersArray[1] = new Misere_Player<char>(player2Name, player2Symbol, nullptr);
    } else if (choice == 2) {
        playersArray[1] = new Random_Misere_Player<char>(player2Symbol, nullptr);
    }

    // Initialize the board for the game with players array
    Misere<char>* B = new Misere<char>(playersArray);

    // Set the board pointer in players
    playersArray[0]->setBoard(B);
    playersArray[1]->setBoard(B);

    // Initialize the GameManager with the board and the players
    GameManager<char> game(B, playersArray);

    // Run the game
    game.run();

    // Clean up dynamically allocated memory
    delete playersArray[0];
    delete playersArray[1];
    delete B;

    return 0;
}
