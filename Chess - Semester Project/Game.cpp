/*
* Last Edited: 5/8/26
* Author: Rayyan
* Description:
*		
*/

#include "Game.h"
#include "GUI.h"

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
	GUIEnabled = false; // Default to console interface, can be changed to true to use GUI
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
	Interface::renderHeader();
	// menu to choose between GUI and Console Interface
	int choice;
	cout << BOLD + GREEN + "\n     ---- Choose Interface ----" << endl;
	cout << "      1. Console Interface" << endl;
	cout << "         2. GUI Interface" << endl;
	cout << "           Choice: " + RESET + DYELLOW;
	cin >> choice;
	cout << RESET;
	if (choice == 2)
		GUIEnabled = true;
	GUI::init(GUIEnabled);

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
		if (GUIEnabled)
			GUI::getMoveInput(from, to);
		else
			Interface::getMoveInput(from, to);

		// Keep asking for input until a valid move is made
		while (!processTurn())
		{
			generateFrame(true);
			GUI::playErrorSound();
			if (GUIEnabled)
				GUI::getMoveInput(from, to);
			else
				Interface::getMoveInput(from, to);

		}

		// Break the Game loop when checkmate or stalemate or 50 move rule is reached 
		if (Checkmate)
		{
			generateFrame();
			cout << endl << RED + "Checkmate Game over! " + RESET << ((currentPlayer == WHITE) ? (GRAY + "Black" + RESET) : (WHITE_ + "White" + RESET)) << RED + " Won " + RESET << endl;
			break;
		}
		else if (Stalemate)
		{
			generateFrame();
			cout << endl << YELLOW + "Stalemate Game over! Its a Draw." + RESET << endl;
			break;
		}
		else if (board->fiftyMoveRule())
		{
			generateFrame();
			cout << endl << YELLOW + "50 Move Rule Game over! Its a Draw." + RESET << endl;
			break;
		}
		else if (board->threeFoldRepetition())
		{
			generateFrame();
			cout << endl << YELLOW + "Three Fold Repetition Game over! Its a Draw." + RESET << endl;
			break;
		}
		else
		{
			changeTurn(); // change turn after a successful loop
		}
	}

}

void Game::generateFrame(bool invalidMove)
{
	system("cls");
	if (GUIEnabled)
	{
		GUI::renderHeader();
		GUI::renderBoard(*board, inCheck);
		GUI::renderCheckAlert(inCheck);
		GUI::renderCurrentPlayer(currentPlayer);
		GUI::renderMoveHistory(board->getMoveHistory());
		GUI::displayWindow();
	}
	else
	{
		Interface::renderHeader();
		Interface::renderBoard(*board, inCheck);
		if (invalidMove)
			cout << RED << "Invalid Move! Please try again." << RESET;
		Interface::renderCheckAlert(inCheck);
		Interface::renderCurrentPlayer(currentPlayer);
		Interface::renderMoveHistory(board->getMoveHistory());
	}
}

bool Game::processTurn()
{
	if (!validatePiece(from))
	{
		cout << RED << "You must move your own piece!" << RESET << endl;
		return false;
	}

	// Block in valid move
	if (!board->movePiece(from, to, GUIEnabled, false))
		return false;

	// after Player makes a move check if other player is in check or not
	inCheck = board->computeCheck((currentPlayer == WHITE) ? BLACK : WHITE);
	if (inCheck)
		GUI::playCheckSound();

	// if in check and no moves availiable other player is in checkmate other if not in check but no availiable moves other player in stalemate
	if (inCheck)
	{
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Checkmate = true;
	}
	else
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Stalemate = true;

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



void Game::EndGame()
{
	system("pause");
	delete this->board;
	this->board = nullptr;
	GUI::close();
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}