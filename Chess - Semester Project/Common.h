
//Contains Global constants and Type Def

/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
	Added Enum for Color and PieceType
	And a Struct for Position, which will be used as Coordinates.
	And created Const variables for ANSI codes which will be used for Output Formatting
*/

#pragma once
using namespace std;

// Pre-Built Librarires
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Global Constants and Type Definitions

enum Color { NONE, WHITE, BLACK }; // Enum for the color of the pieces, NONE is used for empty squares.
enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING }; // Enum for the type of pieces, EMPTY is used for empty squares.
struct Position { int row; int col; }; // Struct for representing the position of pieces on the board, with row and column as coordinates.

// ANSI/style codes
// Example : cout << BOLD + GREEN + "Hello World!" + RESET << endl;
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";
const string STRIKETHROUGH = "\033[9m";
const string ITALIC = "\033[3m";
const string GRAY = "\033[90m";
const string RED = "\033[91m";
const string GREEN = "\033[92m";
const string YELLOW = "\033[93m";
const string BLUE = "\033[94m";
const string MAGENTA = "\033[95m";
const string CYAN = "\033[96m";
const string WHITE_ = "\033[97m";
const string DYELLOW = "\033[33m";
const string DCYAN = "\033[36m";