/*
* Last Edited: 5/8/26
* Author: Armaghan
* Description:
		Implemented: getPromotionInput to get user input for pawn promotion, ensuring only valid piece types (Q/R/B/N) are accepted and returned as PieceType enums.
*/

#include "Interface.h"

void Interface::renderHeader()
{
    cout << BOLD << DCYAN << R"(
    ____  _   _  ____  ____  ____  
   / ___|| | | ||  __|| __/ / ___| 
  | |    | |_| || |__ | |__  \ \   
  | |    |  _  ||  __||  __|  \ \  
  | |___ | | | || |__ | |__  __\ \ 
   \____||_| |_||____||____||____/ 
                                     
  =================================
  -----------Scroll down!----------
    )" << RESET;
}

void Interface::renderBoard(const Board& board, bool isCheck)
{
    // Top border logic
    string horizontalLine = (isCheck ? RED : CYAN) + "  +---+---+---+---+---+---+---+---+" + RESET;

    cout << "\n";
    for (int r = 0; r < 8; r++)
    {
        cout << horizontalLine << "\n";

        cout << BOLD << (8 - r) << RESET << (isCheck ? RED : CYAN) + " |" + RESET;  // Use 8-r to display row numbers from 8 down to 1

        for (int c = 0; c < 8; c++)
        {
            Piece* p = board.getPiece(Position{ r, c });
            if (p == nullptr)
            {
                cout << (isCheck ? RED : CYAN) + "   |" + RESET; // Empty square space
            }
            else
            {
                cout << " " << (p->getColor() == WHITE ? WHITE_ : GRAY) << p->getSymbol() << RESET << (isCheck ? RED : CYAN) + " |" + RESET; // Print the symbol centered in the box
            }
        }
        cout << "\n";
    }

    cout << horizontalLine << "\n"; // Bottom border

    cout << BOLD + "    a   b   c   d   e   f   g   h\n" + RESET; // Column labels a-h
}

void Interface::getMoveInput(Position& from, Position& to)
{
    string inputFrom, inputTo;
    cout << "\n" << BOLD << GREEN << "[PLAYER MOVE]" << RESET << endl;

    do {
        cout << BOLD + DCYAN + "Enter coordinates (i.e a7 a5): " + YELLOW;
        cin >> inputFrom >> inputTo;
        cout << RESET;

        if (inputFrom.length() < 2 || inputFrom.length() > 2 || inputTo.length() < 2 || inputTo.length() > 2)
            continue;

        // Parsing input to row , col 
        from.row = 7 - (inputFrom[1] - '1');
        from.col = inputFrom[0] - 'a';

        to.row = 7 - (inputTo[1] - '1');
        to.col = inputTo[0] - 'a';

    } while (!isValidInput(from.row, from.col) || !isValidInput(to.row, to.col));

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

void Interface::renderCheckAlert(bool inCheck)
{
    if (inCheck)
        cout << "\n" << BOLD << RED << "[CHECK ALERT: Your King is in Danger!]" << RESET;
}

PieceType Interface::getPromotionInput()
{
    string input;
	
    while(true)
    {
        cout << "\n" << BOLD << GREEN << "[PAWN PROMOTION]" << RESET << endl;
        cout << BOLD + DCYAN + "Promote to (Q/R/B/N): " + YELLOW;
        cin >> input;
        cout << RESET;
        if (input.length() != 1)
        {
            cout << RED << "Invalid Input! Please enter a single letter (Q/R/B/N)" << RESET << endl;
            continue;
        }

        char choice = toupper(input[0]);
        switch (choice)
        {
        case 'Q': 
            return QUEEN;
        case 'R':
            return ROOK;
        case 'B':
            return BISHOP;
        case 'N': 
            return KNIGHT;
        default: 
            cout << RED << "Invalid choice! Please choose Q (Queen), R (Rook), B (Bishop), or N (Knight)." << RESET << endl;
            break;
        }
        
	} 
}