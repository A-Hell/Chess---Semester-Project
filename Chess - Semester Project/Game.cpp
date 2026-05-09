
/*
* Last Edited: 5/8/26
* Author: Rayyan
* Description:
*		Implemented: fifty move rule, forces a draw if no captures happen in 50 moves
*		Implemented: Move history, keeps track of the last 100 moves in a 2d array
*/

#include "Game.h"

Game::Game()
{
	// Initialize the game state
	this->board = nullptr;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	inCheck = false;
	Checkmate = false;
	Stalemate = false;
}

void Game::StartGame()
{
	this->board = new Board;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	inCheck = false;
	Checkmate = false;
	Stalemate = false;
	gameLoop(); // Start the main game loop
}

Board& Game::getBoard()
{
	return *board;
}

void Game::gameLoop()
{
	while (true)
	{
		generateFrame();

		// Get input once
		interface.getMoveInput(from, to);

		// Keep asking for input until a valid move is made
		while (!processTurn())
		{
			generateFrame(true);
			interface.getMoveInput(from, to);
		}

		// Break the Game loop when checkmate or stalemate or 50 move rule is reached 
		if (Checkmate || Stalemate || board->fiftyMoveRule())
		{
			generateFrame();

			if (Checkmate)
				cout << endl << RED + "Checkmate Game over! " + RESET << ((currentPlayer == WHITE) ? (GRAY + "Black" + RESET) : (WHITE_ + "White" + RESET)) << RED + " Won " + RESET << endl;
			if (Stalemate)
				cout << endl << YELLOW + "Stalemate Game over! Its a Draw." + RESET << endl;
			if (board->fiftyMoveRule())
				cout << endl << YELLOW + "50 Move Rule Game over! Its a Draw." + RESET << endl;
			break;
		}
		else
		{
			system("pause");
			changeTurn(); // change turn after a successful loop
		}
	}

}

void Game::generateFrame(bool invalidMove)
{
	system("cls");
	interface.renderHeader();
	interface.renderBoard(*board, inCheck);
	if (invalidMove)
		cout << RED << "Invalid Move! Please try again." << RESET ;
	interface.renderCheckAlert(inCheck);
	interface.renderCurrentPlayer(currentPlayer);
	interface.renderMoveHistory(moveHistory);
}

bool Game::processTurn()
{
	if (!validatePiece(from))
	{
		cout << RED << "You must move your own piece!" << RESET << endl;
		return false;
	}

	// Block in valid move
	if (!board->movePiece(from, to))
		return false;

	// after Player makes a move check if other player is in check or not
	inCheck = board->computeCheck((currentPlayer == WHITE) ? BLACK : WHITE);

	// if in check and no moves availiable other player is in checkmate other if not in check but no availiable moves other player in stalemate
	if (inCheck)
	{
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Checkmate = true;
	}
	else
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Stalemate = true;

	storeMoveHistory(from, to); // store the move in the history after a successful move

	return true;
}

void Game::changeTurn() { currentPlayer = ((currentPlayer == WHITE) ? BLACK : WHITE); }

bool Game::validatePiece(Position at)
{
	// if piece of the color being moved is the same as the player return true
	if (board->getPiece(at))
		if (board->getPiece(at)->getColor() == currentPlayer)
			return true;
		else
			return false;
}

bool Game::getCheckStatus() const { return inCheck; }

void Game::storeMoveHistory(Position from, Position to)
{
	// Shift all previous moves back by one position
	for (int i = 99; i > 0; i--)
	{
		moveHistory[i][0] = moveHistory[i - 1][0];
		moveHistory[i][1] = moveHistory[i - 1][1];
	}
	// store the new move at the beginning of the history
	moveHistory[0][0] = from;
	moveHistory[0][1] = to;
}

void Game::EndGame()
{
	system("pause");
	delete this->board;
	this->board = nullptr;
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}