
/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
*		Implemented genreateFrame and getBoard functions.
*/

#include "Game.h"

Game::Game()
{
	this->board = nullptr;
	from = { -1,-1 };
	to = { -1,-1 };
}

void Game::StartGame()
{
	this->board = new Board;
	generateFrame();
}

Board& Game::getBoard()
{
	return *board;
}

void Game::generateFrame()
{
	while (true)
	{
		system("cls");
		interface.renderBoard(*board);
		interface.getMoveInput(from, to);
		while (!board->movePiece(from, to))
		{
			interface.renderBoard(*board);
			cout << "Invalid Move! Please try again." << endl;
			interface.getMoveInput(from, to);
		}
		system("pause");
	}

}

void Game::EndGame()
{
	delete this->board;
	this->board = nullptr;
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}