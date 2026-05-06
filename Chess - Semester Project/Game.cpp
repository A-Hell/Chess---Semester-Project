
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
}

Board& Game::getBoard()
{
	return *board;
}

void Game::generateFrame()
{
	system("cls");
	interface.renderBoard(*board);
	interface.getMoveInput(from, to);
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