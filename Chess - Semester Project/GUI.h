// This header file defines the GUI class
// Since main portion of the code is done we will now move to the bonus part of the project
// This is supposed to replace the Interface class exactly and fit right in with rest of the code but instead of using console output it will use SFML

/*
* Last Edited: 5/8/26
* Author: Armaghan
* Description:
*           Declared: All functions that were in Interface class
*           Added: Init() to load all textures and Dyncamically allocate the Window
*           Added: close() to clean up the window and any resources
*           Added: renderBoard() to draw the chessboard and pieces on the screen
*           Added: getMoveInput() to capture user input for moves using mouse clicks
*           Added: isValidInput() to ensure the user clicks within the range of the chessboard
*/

#pragma once
#include "Common.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

struct pieceTexture { char symbol; sf::Texture texture; };

class GUI
{
private:

	static unsigned int windowWidth;
	static unsigned int windowHeight;
    static unsigned int boardSize;
    static float tileSize;

    static sf::RenderWindow* window;
    static sf::Font font;
    static bool fontLoaded;

    static pieceTexture pieceTextures[12];
    static sf::Texture boardTexture;
    static bool texturesLoaded;

public:
    static void init();

	// Rendering functions
    static void renderHeader();
    static void renderBoard(const Board& board, bool isCheck = false);
    static void renderCurrentPlayer(Color currentPlayer);
    static void renderCheckAlert(bool inCheck);
    static void renderMoveHistory(const Position moveHistory[100][2]);

	// Input functions
    static void getMoveInput(Position& from, Position& to);
    static bool isValidInput(int row, int col);
    static PieceType getPromotionInput();

    static void close();
};
