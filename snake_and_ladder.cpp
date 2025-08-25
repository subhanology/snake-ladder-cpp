#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to print a row separator
void Separator() {
    cout << "+------+------+------+------+------+------+------+------+------+------+\n";
}

// Function to display the board with borders around each number
void displayBoard(int P1, int P2) {
    int counter = 100; // Starting number for the board
    Separator();  // Print the topmost border

    for (int i = 0; i < 10; i++) {
        cout << "|"; // Start of row

        for (int j = 0; j < 10; j++) {
            // Calculate the cell number based on row direction (zig-zag pattern)
            int cell;
            if (i % 2 == 0) {
                cell = counter - j; // Even row: left to right
            }
            else {
                cell = counter - (9 - j); // Odd row: right to left
            }

            // Display cell content based on player positions
            if (P1 == cell && P2 == cell) {
                cout << "  B   |";  // Both players in the same cell
            }
            else if (P1 == cell) {
                cout << "  P1  |";  // Player 1 position
            }
            else if (P2 == cell) {
                cout << "  P2  |";  // Player 2 position
            }
            else {
                cout << setw(5) << cell << " |"; // Board numbers with alignment
            }
        }

        cout << "\n";       // Move to the next line
        Separator();  // Print the separator line
        counter -= 10;     // Move to the next row's starting number
    }
}

// Function to handle snakes and ladders
int checkPosition(int position) {
    int snakes[5][2] = { {44, 20}, 
                         {52, 5}, 
                         {72, 37}, 
                         {91, 61}, 
                         {99, 69} };
    
    int ladders[5][2] = { {2, 23}, 
                          {8, 34}, 
                          {30, 50}, 
                          {61, 79}, 
                          {70, 92} };

    for (int i = 0; i < 5; i++) {
        if (position == snakes[i][0]) {
            cout << "Hiss!! You stepped on a snake. Now moving to position " << snakes[i][1] << endl;
            return snakes[i][1]; //Move to lower position if stepped on snake
        }
        if (position == ladders[i][0]) {
            cout << "Hooray!! You stepped on a ladder. Now moving to position " << ladders[i][1] << endl;
            return ladders[i][1]; //Move to upper position if stepped on ladder
        }
    }

    return position; // No change
}

// Main function
int main() {
    srand((time(0)));

    int P1 = 0, P2 = 0; // Start positions at 0 for both players
    bool player1Turn = true;

    cout << "Welcome to Snake and Ladder Game!\n";
    cout << "Reach position 100 to win.\n";
	cout << "Stepping on Snake head will move you down to Snake tail!\n";
	cout << "While, Stepping on Ladder bottom will move you up to Ladder top\n" << endl;

    while (true) {
        displayBoard(P1, P2);

        if (player1Turn) {
            cout << "Player 1, press Enter to roll the dice...";
        }
        else {
            cout << "Player 2, press Enter to roll the dice...";
        }
        cin.ignore(); // Wait for player to press Enter

        int dice = (rand() % 6) + 1; // Roll dice (1 to 6)
        if (player1Turn) {
            cout << "Player 1 rolls a " << dice << ".\n";
        }
        else {
            cout << "Player 2 rolls a " << dice << ".\n";
        }

        if (player1Turn)
            P1 += dice; // Player 1 position updates based on dice roll
        else
            P2 += dice; // Player 2 position updates based on dice roll

        // Ensure players don�t exceed position 100
        if (player1Turn && P1 > 100) {
            P1 -= dice;
            cout << "Your dice count exceed the board limit. You're on the same position\n" << endl; // Player 1 can't go beyond position 100
        }
        else if (!player1Turn && P2 > 100) {
            P2 -= dice;
            cout << "Your dice count exceed the board limit. You're on the same position\n" << endl; // Player 2 can't go beyond position 100
        }
        // Check for snakes or ladders
        if (player1Turn)
            P1 = checkPosition(P1);
        else
            P2 = checkPosition(P2);

        // Check if a player has won
        if (P1 == 100) {
            displayBoard(P1, P2);
            cout << "Player 1 wins!\n";
            break;
        }
        else if (P2 == 100) {
            displayBoard(P1, P2);
            cout << "Player 2 wins!\n";
            break;
        }
        
        cout << "\n";

        player1Turn = !player1Turn; // Switch turns
    }

    return 0;
}
