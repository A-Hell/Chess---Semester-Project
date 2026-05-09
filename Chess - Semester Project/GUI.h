// This header file defines the GUI class
// Since main portion of the code is done we will now move to the bonus part of the project
// This is supposed to replace the Interface class exactly and fit right in with rest of the code but instead of using console output it will use SFML

/*
* Last Edited: 5/8/26
* Author: Armaghan
* Description:
*           Added: Sound Effects for moves, captures, checks, promotions, castling, and errors
*           Added: Visual Effect for chosen piece (highlighting the square of the piece being moved)  
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

    static sf::SoundBuffer moveSoundBuffer;
    static sf::SoundBuffer captureSoundBuffer;
    static sf::SoundBuffer notifySoundBuffer;
    static sf::SoundBuffer checkSoundBuffer;
    static sf::SoundBuffer promoteSoundBuffer;
    static sf::SoundBuffer castleSoundBuffer;
    static sf::SoundBuffer errorSoundBuffer;

    static sf::Sound* moveSound;
    static sf::Sound* captureSound;
    static sf::Sound* notifySound;
    static sf::Sound* checkSound;
    static sf::Sound* promoteSound;
    static sf::Sound* castleSound;
    static sf::Sound* errorSound;

    static bool soundsLoaded;

    // Visual Effect for chosen piece
    static const Board* cachedBoard;
    static Position highlightSquare;

public:
    static void init(bool activeGUI = false);

    // Rendering functions
    static void renderHeader();
    static void renderBoard(const Board& board, bool isCheck = false);
    static void renderCurrentPlayer(Color currentPlayer);
    static void renderCheckAlert(bool inCheck);
    static void renderMoveHistory(const Position moveHistory[100][2]);

    // Sound functions -- These Sounds Work Independatly of GUI or Interface
    // since they use SFML's audio module, they are placed here
    static void playMoveSound();
    static void playCaptureSound();
    static void playNotifySound();
    static void playCheckSound();
    static void playPromoteSound();
    static void playCastleSound();
    static void playErrorSound();

    // Input functions
    static void getMoveInput(Position& from, Position& to);
    static bool isValidInput(int row, int col);
    static PieceType getPromotionInput();

    static void close();
};
