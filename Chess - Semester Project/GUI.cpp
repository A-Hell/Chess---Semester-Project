/*
* Last Edited: 5/9/26
* Author: Armaghan
* Description:
*           Modified: init() to draw window only if GUI selected
*           Implemented: Sounds for moves, captures, checks, promotions, castling, and errors
*           Implemented: Visual Effect for chosen piece 
*/

#include "GUI.h"
#include <iostream>
using namespace std;


// Control REsolution and board size
unsigned int GUI::windowWidth = 1024;
unsigned int GUI::windowHeight = 720;
unsigned int GUI::boardSize = 720;
float GUI::tileSize = boardSize / 8.0;

// Initialize Variables with placeholder values
sf::RenderWindow* GUI::window = nullptr;
sf::Font GUI::font;
bool GUI::fontLoaded = false;
pieceTexture GUI::pieceTextures[12];
sf::Texture GUI::boardTexture;
bool GUI::texturesLoaded = false;

sf::SoundBuffer GUI::moveSoundBuffer;
sf::SoundBuffer GUI::captureSoundBuffer;
sf::SoundBuffer GUI::notifySoundBuffer;
sf::SoundBuffer GUI::checkSoundBuffer;
sf::SoundBuffer GUI::promoteSoundBuffer;
sf::SoundBuffer GUI::castleSoundBuffer;
sf::SoundBuffer GUI::errorSoundBuffer;

sf::Sound* GUI::moveSound = nullptr;
sf::Sound* GUI::captureSound = nullptr;
sf::Sound* GUI::notifySound = nullptr;
sf::Sound* GUI::checkSound = nullptr;
sf::Sound* GUI::promoteSound = nullptr;
sf::Sound* GUI::castleSound = nullptr;
sf::Sound* GUI::errorSound = nullptr;

bool GUI::soundsLoaded = false;
const Board* GUI::cachedBoard = nullptr;
Position GUI::highlightSquare = {-1, -1};

void GUI::init(bool activeGUI)
{
    if (activeGUI)
    {
        if (!window)
        {
            window = new sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Chess Game");
            if (!fontLoaded)
            {
                if (font.openFromFile("C:/Windows/Fonts/arial.ttf"))
                    fontLoaded = true;
            }
            if (!texturesLoaded)
            {
                std::string basePath = "../Assets/Sprites/";
                boardTexture.loadFromFile(basePath + "board.png");

                if (boardTexture.getSize().x > 0) // successfully loaded
                {
                    pieceTextures[0].symbol = 'P'; pieceTextures[0].texture.loadFromFile(basePath + "chess-pawn-white.png");
                    pieceTextures[1].symbol = 'p'; pieceTextures[1].texture.loadFromFile(basePath + "chess-pawn-black.png");
                    pieceTextures[2].symbol = 'R'; pieceTextures[2].texture.loadFromFile(basePath + "chess-rook-white.png");
                    pieceTextures[3].symbol = 'r'; pieceTextures[3].texture.loadFromFile(basePath + "chess-rook-black.png");
                    pieceTextures[4].symbol = 'N'; pieceTextures[4].texture.loadFromFile(basePath + "chess-knight-white.png");
                    pieceTextures[5].symbol = 'n'; pieceTextures[5].texture.loadFromFile(basePath + "chess-knight-black.png");
                    pieceTextures[6].symbol = 'B'; pieceTextures[6].texture.loadFromFile(basePath + "chess-bishop-white.png");
                    pieceTextures[7].symbol = 'b'; pieceTextures[7].texture.loadFromFile(basePath + "chess-bishop-black.png");
                    pieceTextures[8].symbol = 'Q'; pieceTextures[8].texture.loadFromFile(basePath + "chess-queen-white.png");
                    pieceTextures[9].symbol = 'q'; pieceTextures[9].texture.loadFromFile(basePath + "chess-queen-black.png");
                    pieceTextures[10].symbol = 'K'; pieceTextures[10].texture.loadFromFile(basePath + "chess-king-white.png");
                    pieceTextures[11].symbol = 'k'; pieceTextures[11].texture.loadFromFile(basePath + "chess-king-black.png");

                    boardTexture.setSmooth(true);
                    for (int i = 0; i < 12; i++)
                        pieceTextures[i].texture.setSmooth(true);

                    texturesLoaded = true;
                }
            }
        }
    }
    if (!soundsLoaded)
    {
        if (moveSoundBuffer.loadFromFile("../Assets/Sounds/move.mp3") &&
            captureSoundBuffer.loadFromFile("../Assets/Sounds/capture.mp3") &&
            notifySoundBuffer.loadFromFile("../Assets/Sounds/notify.mp3") &&
            checkSoundBuffer.loadFromFile("../Assets/Sounds/check.mp3") &&
            promoteSoundBuffer.loadFromFile("../Assets/Sounds/promote.mp3") &&
            castleSoundBuffer.loadFromFile("../Assets/Sounds/castle.mp3") &&
            errorSoundBuffer.loadFromFile("../Assets/Sounds/error.mp3"))
        {
            moveSound = new sf::Sound(moveSoundBuffer);
            captureSound = new sf::Sound(captureSoundBuffer);
            notifySound = new sf::Sound(notifySoundBuffer);
            checkSound = new sf::Sound(checkSoundBuffer);
            promoteSound = new sf::Sound(promoteSoundBuffer);
            castleSound = new sf::Sound(castleSoundBuffer);
            errorSound = new sf::Sound(errorSoundBuffer);
            soundsLoaded = true;
        }
    }
}

void GUI::close()
{
    if (window)
    {
        window->close();
        delete window;
        window = nullptr;
    }
    if (moveSound) { delete moveSound; moveSound = nullptr; }
    if (captureSound) { delete captureSound; captureSound = nullptr; }
    if (notifySound) { delete notifySound; notifySound = nullptr; }
    if (checkSound) { delete checkSound; checkSound = nullptr; }
    if (promoteSound) { delete promoteSound; promoteSound = nullptr; }
    if (castleSound) { delete castleSound; castleSound = nullptr; }
    if (errorSound) { delete errorSound; errorSound = nullptr; }
}

void GUI::renderHeader()
{
    // Draw header
}

void GUI::renderBoard(const Board& board, bool isCheck)
{
    // store board for in Move changes
    cachedBoard = &board;

    if (!window) return;
    window->clear(sf::Color(50, 50, 50));

	// Render the board background if texture is loaded
    if (texturesLoaded)
    {
        sf::Sprite boardSprite(boardTexture);
        boardSprite.setScale({boardSize / boardSprite.getLocalBounds().size.x, boardSize / boardSprite.getLocalBounds().size.y});
        window->draw(boardSprite);
    }

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
			// Safety net for if textures fail to load, manually draw the board with colored squares
            // used to be the go to before i found the actual tectures
            if (!texturesLoaded)
            {
                sf::RectangleShape tile(sf::Vector2f({tileSize, tileSize}));
                tile.setPosition({c * tileSize, r * tileSize});

                if ((r + c) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181)); // Light square
                else
                    tile.setFillColor(sf::Color(181, 136, 99)); // Dark square

                window->draw(tile);
            }

            // Draw piece as well if we want
            Piece* p = board.getPiece(Position{ r, c });
            if (p != nullptr)
            {
                int textureIndex = -1;
                if (texturesLoaded) {
                    for (int i = 0; i < 12; i++) {
                        if (pieceTextures[i].symbol == p->getSymbol()) {
                            textureIndex = i;
                            break;
                        }
                    }
                }

                if (texturesLoaded && textureIndex != -1)
                {
                    sf::Sprite sprite(pieceTextures[textureIndex].texture);
                    sf::FloatRect bounds = sprite.getLocalBounds();
                    // adjust scale to make piece fit a bit inside the tile
                    sprite.setScale({(tileSize * 0.9f) / bounds.size.x, (tileSize * 0.9f) / bounds.size.y});

					// center the piece in the tile
					float xOff = (tileSize - tileSize * 0.9f) / 2.0f;
					float yOff = (tileSize - tileSize * 0.9f) / 2.0f;

					// If it's the highlighted piece, move it up slightly to create a floating effect
					if (r == highlightSquare.row && c == highlightSquare.col) {
						yOff -= 15.0f; 
					}

					sprite.setPosition({c * tileSize + xOff, r * tileSize + yOff});
					window->draw(sprite);
				}
				// Safety Net for when Piece textures fail to load
				else if (fontLoaded)
				{
					sf::Text text(font, std::string(1, p->getSymbol()), 30);
					if (p->getColor() == WHITE)
						text.setFillColor(sf::Color::White);
					else
						text.setFillColor(sf::Color::Black);

					float txtYOff = 5.0f;
					if (r == highlightSquare.row && c == highlightSquare.col) {
						txtYOff -= 10.0f;
					}
					text.setPosition({c * tileSize + 10.0f, r * tileSize + txtYOff});
					window->draw(text);
				}
            }
        }
    }
    window->display();
}

void GUI::getMoveInput(Position& from, Position& to)
{
    bool fromSelected = false;
    from.row = -1; from.col = -1;
    to.row = -1; to.col = -1;

    if (!window) return;

    while (window->isOpen())
    {
        while (std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
                exit(0);
            }
            if (auto mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button == sf::Mouse::Button::Left)
                {
                    int c = mouseButton->position.x / tileSize;
                    int r = mouseButton->position.y / tileSize;
                    if (isValidInput(r, c))
                    {
                        if (!fromSelected)
                        {
                            from.row = r;
                            from.col = c;
                            fromSelected = true;
                            highlightSquare = from;
                            if (cachedBoard) {
                                renderBoard(*cachedBoard, false);
                            }
                        }
                        else
                        {
                            to.row = r;
                            to.col = c;
                            highlightSquare = {-1, -1}; // reset floating
                            return;
                        }
                    }
                }
            }
        }
    }
}

bool GUI::isValidInput(int row, int col)
{
    return row >= 0 && row <= 7 && col >= 0 && col <= 7;
}

void GUI::renderCurrentPlayer(Color currentPlayer)
{
    // Implementation
}

void GUI::renderCheckAlert(bool inCheck)
{
    // Implementation
}

void GUI::renderMoveHistory(const Position moveHistory[100][2])
{
    // Implementation
}

PieceType GUI::getPromotionInput()
{
    return QUEEN; // Default to Queen for now
}

void GUI::playMoveSound()
{
    if (soundsLoaded && moveSound) moveSound->play();
}

void GUI::playCaptureSound()
{
    if (soundsLoaded && captureSound) captureSound->play();
}

void GUI::playNotifySound()
{
    if (soundsLoaded && notifySound) notifySound->play();
}

void GUI::playCheckSound()
{
    if (soundsLoaded && checkSound) checkSound->play();
}

void GUI::playPromoteSound()
{
    if (soundsLoaded && promoteSound) promoteSound->play();
}

void GUI::playCastleSound()
{
    if (soundsLoaded && castleSound) castleSound->play();
}

void GUI::playErrorSound()
{
    if (soundsLoaded && errorSound) errorSound->play();
}
