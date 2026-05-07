/*
* Last Edited: 5/7/26
* Author: Armaghan
* Description:
	Updated line 24 to use Position instead of separate row and col variables, to match updated getPiece parameters
	modified line 32 to print colored piece symbols for better visualization of the board.
*/

#include "Interface.h"

void Interface::renderBoard(const Board& board)
{
    // Top border logic
    string horizontalLine = "  +---+---+---+---+---+---+---+---+";

    cout << "\n";
    for (int r = 0; r < 8; r++)
    {
        cout << horizontalLine << "\n";

        cout << (8 - r) << " |";  // Use 8-r to display row numbers from 8 down to 1

        for (int c = 0; c < 8; c++)
        {
            Piece* p = board.getPiece(Position{r, c});
            if (p == nullptr)
            {
                cout << "   |"; // Empty square space
            }
            else
            {
                cout << " " << BOLD + (p->getColor() == WHITE ? WHITE_ : GRAY) << p->getSymbol() << RESET << " |"; // Print the symbol centered in the box
            }
        }
        cout << "\n";
    }

    cout << horizontalLine << "\n"; // Bottom border

    cout << "    a   b   c   d   e   f   g   h\n"; // Column labels a-h
}

void Interface::getMoveInput(Position& from, Position& to)
{
    string input;
    cout << "\n" << BOLD << GREEN << "[PLAYER MOVE]" << RESET << endl;

    do {
        cout << "Enter 'From' coordinates (i.e a7): ";
        cin >> input;

        if (input.length() < 2 || input.length() > 2)
            continue;
        
        // Parsing input to row , col 
        from.row = 7 - (input[1] - 49);
        from.col = input[0] - 97;

    } while (!isValidInput(from.row, from.col));

    do {
        cout << "Enter 'To' coordinates (i.e a7): ";
        cin >> input;

        if (input.length() < 2 || input.length() > 2) // discard improper input
            continue;

        // Parsing input to row , col 
        to.row = 7 - (input[1] - 49);
        to.col = input[0] - 97;

    } while (!isValidInput(to.row, to.col));
}

bool Interface::isValidInput(int row, int col)
{
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
    {
        return true;
    }
    cout << RED << "Invalid coordinate! Use range 0-7." << RESET << endl;
    return false;
}

void Interface::renderCurrentPlayer(Color currentPlayer)
{
    cout << "\n" << BOLD << GREEN << "[CURRENT PLAYER: " << (currentPlayer == WHITE ? (WHITE_ + "WHITE") : (GRAY + "BLACK")) << GREEN + "]" << RESET << endl;
}