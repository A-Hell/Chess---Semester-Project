/*
* Last Edited: 5/10/26
* Author: Armaghan
* Description:
*           Implemented: renderMoveHistory to display the history of moves made, since we had more space here it show 10 moves instead of 5 like the console interface
*           Implemented: getPromotionInput which uses 4 standard buttons and forces the user to choose a piece for promotion
*           Added: renderEndGame to display the result of the game and reason for endgame, and then forces the user to exit bcz console does the same
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
Color GUI::cachedCurrentPlayer = WHITE;
bool GUI::cachedInCheck = false;
Position GUI::highlightSquare = {-1, -1};
static Position cachedMoveHistoryArray[100][2];
static bool moveHistoryCached = false;

void GUI::init(bool activeGUI)
{
    if (activeGUI)
    {
        if (!window)
        {
            window = new sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Chess Game", sf::Style::Titlebar | sf::Style::Close);
            if (!fontLoaded)
            {
                if (font.openFromFile("C:/Windows/Fonts/calibri.ttf"))
                    fontLoaded = true;
            }
            if (!texturesLoaded)
            {
                string basePath = "../Assets/Sprites/";
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
    if (!window || !fontLoaded) return;

    window->clear(sf::Color(50, 50, 50));

    // Background for the side panel (island)
    sf::RectangleShape sidePanel(sf::Vector2f((float)(windowWidth - boardSize), (float)windowHeight));
    sidePanel.setPosition({ (float)boardSize, 0.0f });
    sidePanel.setFillColor(sf::Color(40, 40, 40));
    window->draw(sidePanel);

    // Header Text
    sf::Text header(font, "Chess Game", 42);
    header.setFillColor(sf::Color::Cyan);
    header.setStyle(sf::Text::Bold);

    // Center the header horizontally in the side panel
    sf::FloatRect textRect = header.getLocalBounds();
    header.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
    header.setPosition({ boardSize + (windowWidth - boardSize) / 2.0f, 40.0f });

    window->draw(header);
}

void GUI::renderBoard(const Board& board, bool isCheck)
{
	// store board for in Move changes
	cachedBoard = &board;

	if (!window) return;

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
					sf::Text text(font, string(1, p->getSymbol()), 30);
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

			// Draw Coordinates (Top row and Leftmost column)
			if (fontLoaded)
			{
				// Rightmost column: draw 1-8 (mapped from r)
				if (c == 7)
				{
					sf::Text rankText(font, to_string(8 - r), 14);
					rankText.setFillColor((r + c) % 2 == 0 ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181));
					rankText.setStyle(sf::Text::Bold);
					// Draw near the top right of the rightmost tiles
					rankText.setPosition({ c * tileSize + tileSize - 20.0f, r * tileSize + 10.0f });
					window->draw(rankText);
				}

				// Top row: draw a-h 
				if (r == 0)
				{
					sf::Text fileText(font, string(1, 'a' + c), 14);
					fileText.setFillColor((r + c) % 2 == 0 ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181));
					fileText.setStyle(sf::Text::Bold);
					// Draw in top left corner of the tile
					fileText.setPosition({ c * tileSize + 9.0f, 10.0f });
					window->draw(fileText);
				}
			}
		}
	}
}

void GUI::getMoveInput(Position& from, Position& to)
{
    bool fromSelected = false;
    from.row = -1; from.col = -1;
    to.row = -1; to.col = -1;

    if (!window) return;

    while (window->isOpen())
    {
        while (optional event = window->pollEvent())
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
                                window->clear(sf::Color(50, 50, 50));
                                renderHeader();
                                renderBoard(*cachedBoard, false);
                                renderCurrentPlayer(cachedCurrentPlayer);
                                renderCheckAlert(cachedInCheck);
                                if (moveHistoryCached) {
                                    renderMoveHistory(cachedMoveHistoryArray);
                                }
                                window->display();
                            }
                        }
                        else
                        {
                            to.row = r;
                            to.col = c;
                            highlightSquare = {-1, -1}; // reset floating piece
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
    cachedCurrentPlayer = currentPlayer;

    if (!window || !fontLoaded) return;

    string turnStr = (currentPlayer == WHITE) ? "[Current Player: White]" : "[Current Player: Black]";
    sf::Text turnText(font, turnStr, 26);

    // Set color based on player to add a visual cue.
    turnText.setFillColor(currentPlayer == WHITE ? sf::Color(240, 240, 240) : sf::Color(150, 150, 150));
    turnText.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = turnText.getLocalBounds();
    turnText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
    // Position it below the header
    turnText.setPosition({ boardSize + (windowWidth - boardSize) / 2.0f, 100.0f });

    window->draw(turnText);
}

void GUI::renderCheckAlert(bool inCheck)
{
    cachedInCheck = inCheck;

    if (!window || !fontLoaded) return;

    if (inCheck)
    {
		// Red Overlay on the board to indicate danger
        sf::RectangleShape redOverlay(sf::Vector2f((float)boardSize - 10.0f, (float)boardSize - 10.0f));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 30)); // 30 is tranparecy
        window->draw(redOverlay);

		// Draw the Text Alert
        sf::Text alertText(font, "Your King is in Danger!", 28);
        alertText.setFillColor(sf::Color(255, 60, 60));
        alertText.setStyle(sf::Text::Bold);

        sf::FloatRect textRect = alertText.getLocalBounds();
        alertText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f + 5.0f, textRect.position.y + textRect.size.y / 2.0f  + 5.0f});
        // Put it below current player
        alertText.setPosition({ boardSize + (windowWidth - boardSize) / 2.0f + 7.0f, 140.0f });

        window->draw(alertText);
    }
}

void GUI::renderMoveHistory(const Position moveHistory[100][2])
{
    if (!window || !fontLoaded) return;

    // Cache the move history so it can be re-rendered during hovering/selection updates
    for (int i = 0; i < 100; i++) {
        cachedMoveHistoryArray[i][0] = moveHistory[i][0];
        cachedMoveHistoryArray[i][1] = moveHistory[i][1];
    }
    moveHistoryCached = true;

    // Title
    sf::Text title(font, "Move History", 24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Underlined);

    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin({ titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f });
    title.setPosition({ boardSize + (windowWidth - boardSize) / 2.0f, 200.0f });
    window->draw(title);

    // Count valid moves
    int moveCount = 0;
    for (int i = 0; i < 100; i++)
    {
        // if a move is empty Skip it
        if (moveHistory[i][0].row == 0 && moveHistory[i][0].col == 0 && moveHistory[i][1].row == 0 && moveHistory[i][1].col == 0)
            continue;
        moveCount++;
    }

    // Only show last 10 moves
    int startIdx = 0;
	int endIdx = (moveCount > 10 ? 10 : moveCount);
    float startY = 240.0f;

    for (int i = startIdx; i < endIdx; i++)
    {

        string moveStr = to_string(moveCount - i ) + ". ";
        moveStr += (char)('a' + moveHistory[i][0].col);
        moveStr += to_string(8 - moveHistory[i][0].row);
        moveStr += " -> ";
        moveStr += (char)('a' + moveHistory[i][1].col);
        moveStr += to_string(8 - moveHistory[i][1].row);

        sf::Text moveText(font, moveStr, 18);
        moveText.setFillColor(sf::Color(200, 200, 200));

        sf::FloatRect textRect = moveText.getLocalBounds();
        moveText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
        moveText.setPosition({ boardSize + (windowWidth - boardSize) / 2.0f, startY + (i - startIdx) * 28.0f });

        window->draw(moveText);
    }
}

PieceType GUI::getPromotionInput()
{
    if (!window || !fontLoaded) return QUEEN; // Default if no window

    float promptY = 550.0f;
    float panelCenter = boardSize + (windowWidth - boardSize) / 2.0f;

    sf::Text prompt(font, "Pawn Promotion", 24);
    prompt.setFillColor(sf::Color::Yellow);
    prompt.setStyle(sf::Text::Bold);
    sf::FloatRect promptRect = prompt.getLocalBounds();
    prompt.setOrigin({ promptRect.position.x + promptRect.size.x / 2.0f, promptRect.position.y + promptRect.size.y / 2.0f });
    prompt.setPosition({ panelCenter, promptY });

    string options[4] = { "Queen", "Rook", "Bishop", "Knight" };
    PieceType types[4] = { QUEEN, ROOK, BISHOP, KNIGHT };
    sf::RectangleShape buttons[4];
    optional<sf::Text> btnTexts[4];

    for (int i = 0; i < 4; i++) {
        buttons[i].setSize({ 100.0f, 35.0f });
        buttons[i].setFillColor(sf::Color(80, 80, 80));
        buttons[i].setOutlineThickness(2.0f);
        buttons[i].setOutlineColor(sf::Color(120, 120, 120));
        buttons[i].setOrigin({ 50.0f, 17.5f });

        // 2x2 grid for buttons
        float bx = panelCenter + (i % 2 == 0 ? -60.0f : 60.0f);
        float by = promptY + 45.0f + (i / 2) * 45.0f;
        buttons[i].setPosition({ bx, by });

        btnTexts[i].emplace(font, options[i], 18);
        btnTexts[i]->setFillColor(sf::Color::White);

        sf::FloatRect tr = btnTexts[i]->getLocalBounds();
        btnTexts[i]->setOrigin({ tr.position.x + tr.size.x / 2.0f, tr.position.y + tr.size.y / 2.0f });
        btnTexts[i]->setPosition({ bx, by });
    }

    // Render the scene once with the prompt included
    window->clear(sf::Color(50, 50, 50));
    renderHeader();
    if (cachedBoard) renderBoard(*cachedBoard, false);
    renderCurrentPlayer(cachedCurrentPlayer);
    renderCheckAlert(cachedInCheck);
    if (moveHistoryCached) renderMoveHistory(cachedMoveHistoryArray);

    window->draw(prompt);
    for (int i = 0; i < 4; i++) {
        window->draw(buttons[i]);
        window->draw(*btnTexts[i]);
    }
    window->display();

    // Loop until user clicks a valid button
    while (window->isOpen())
    {
        while (optional event = window->pollEvent())
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
                    sf::Vector2f mousePos((float)mouseButton->position.x, (float)mouseButton->position.y);

                    for (int i = 0; i < 4; i++) {
                        if (buttons[i].getGlobalBounds().contains(mousePos)) {
                            return types[i];
                        }
                    }
                }
            }
        }
    }
	// If window is closed without selection, default to Queen
	return QUEEN;
}

void GUI::renderEndGame(char reason)
{
	if (!window || !fontLoaded) return;

	// Render the scene once with the overlay included
	window->clear(sf::Color(50, 50, 50));
	renderHeader();
	if (cachedBoard) renderBoard(*cachedBoard, false);
	renderCurrentPlayer(cachedCurrentPlayer);
	renderCheckAlert(cachedInCheck);
	if (moveHistoryCached) renderMoveHistory(cachedMoveHistoryArray);

	// Gray Overlay on the board to indicate game over
	sf::RectangleShape grayOverlay(sf::Vector2f((float)boardSize - 10.0f, (float)boardSize - 10.0f));
	grayOverlay.setFillColor(sf::Color(60, 60, 60, 180)); // Gray with transparency
	window->draw(grayOverlay);

	string message = "";
	if (reason == 'C') message = (cachedCurrentPlayer == WHITE) ? "Checkmate! White Won" : "Checkmate! Black Won";
	else if (reason == 'S') message = "Stalemate! Draw";
	else if (reason == 'F') message = "50 Move Rule! Draw";
	else if (reason == 'T') message = "3-Fold Repetition! Draw";

	// Draw the Game Over Message 
	sf::Text alertText(font, message, 40);
	alertText.setFillColor(sf::Color::White);
	alertText.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = alertText.getLocalBounds();
	alertText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
	alertText.setPosition({ boardSize / 2.0f, boardSize / 2.0f - 20.0f });

	// Exit prompt
	sf::Text exitPrompt(font, "Press any key or click to exit...", 20);
	exitPrompt.setFillColor(sf::Color(200, 200, 200));
	sf::FloatRect exitRect = exitPrompt.getLocalBounds();
	exitPrompt.setOrigin({ exitRect.position.x + exitRect.size.x / 2.0f, exitRect.position.y + exitRect.size.y / 2.0f });
	exitPrompt.setPosition({ boardSize / 2.0f, boardSize / 2.0f + 40.0f });

	window->draw(alertText);
	window->draw(exitPrompt);
	window->display();

	// Loop until user makes and input to exit
	while (window->isOpen())
	{
		while (optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
				exit(0);
			}
			if (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::MouseButtonPressed>())
			{
				window->close();
				exit(0);
			}
		}
	}
}

void GUI::displayWindow()
{
    if (window)
		window->display();
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
