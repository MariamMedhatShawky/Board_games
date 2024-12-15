#include <string>
#include <vector>
#include <iostream>
#include "Game2.h"
#include "Game5.h"
#include "Game8.h"

using namespace std;

int main() {
    int choice,choice1;
    string playerXName, player2Name;

    while (true) {
        cout << "Choose the game you want to play : " << endl;
        cout << "1) Game 5\n2) Game 2\n3) Game 8\n4) SUS " << endl;
        cin >> choice1;

        if (choice1 == 1) {
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            Game5_Board *B = new Game5_Board();
            // Create players
            vector<int> player1_numbers = {1, 3, 5, 7, 9};
            vector<int> player2_numbers = {2, 4, 6, 8, 10};

            Game5_Player player1("Player 1", 1, player1_numbers);
            Player<int>* player2;
            if (choice == 1) {
                player2 = new Game5_Player("Player 2", 2, player2_numbers);
            }
            else
            {
                player2 = new Game5_RandomPlayer(2, player2_numbers);
            }

            Player<int>* players[] = {&player1, player2};
            player1.setBoard(B);
            player2->setBoard(B);

            // Create and run the game manager
            GameManager<int> gameManager(B, players);
            gameManager.run();
            break;
        }

        else if (choice1 == 2) {

            Player<char>* players[2];
            Game2_Board *B = new Game2_Board();
            players[0] = new Game2_Player("Player 1", 'X');

            while (true){
                cout << "Choose Player 2 type:\n";
                cout << "1. Human\n";
                cout << "2. Random Player\n";
                cout << "3. Ai Player\n";
                cin >> choice;

                if (choice == 1) {
                    players[1] = new Game2_Player("Player 2", 'O');
                    break;
                }
                else if (choice == 2) {
                    players[1] = new Game2_RandomPlayer('O');
                    break;
                }
                else if (choice == 3) {
                    players[1] = new Game2_AIPlayer('O',B);
                    break;
                }
                else {
                    cout << "Invalid choice, please try again.\n";
                    continue;
                }
            }

            GameManager<char> Game2(B, players);
            Game2.run();
            break;
        }

    }

}