int main(){
    // Set up the Ultimate Tic Tac Toe board
            Game8_MainBoard* Board = new Game8_MainBoard();

            // Choose game mode
            int choice;
            cout << "Choose game mode:\n";
            cout << "1. Human vs Human\n";
            cout << "2. Human vs Computer\n";
            cin >> choice;

            Player<char>* player1;
            Player<char>* player2;

            // Set up players based on choice
            if (choice == 1) {
                player1 = new Game8_Player("player 1", 'X');
                player2 = new Game8_Player("player 2", 'O');
            }
            else if (choice == 2) {
                player1 = new Game8_Player("player 1", 'X');
                player2 = new Game8_RandomPlayer('O');
            }
            // Set the board for both players
            player1->setBoard(Board);
            player2->setBoard(Board);

            // Create the game manager and run the game
            Player<char>* players[2] = { player1, player2 };
            GameManager<char>* gameManager = new GameManager<char>(Board, players);
            gameManager->run();

            // Clean up dynamically allocated memory
            delete Board;
            delete player1;
            delete player2;
            delete gameManager;


}