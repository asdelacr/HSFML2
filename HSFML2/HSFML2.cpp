// Aylin Delacruz
// 1306942
// Pong
// SFML/C++

#include "stdafx.h"
#include "Bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Set Window Parameters
#define gameWidth 1100
#define gameHeight 600

// Give Players values to their respective titles
#define player1 1
#define player2 2

using namespace sf;

int main() {

	// Render Window, name the game 'PONG'
	RenderWindow window (VideoMode (gameWidth, gameHeight), "PONG");

	// Creates the classic line in the middle of the board to separate player space
	// I purposefully made the line slanted 
	// for aesthetic reasons
	Vertex line[] = {
		Vertex (Vector2f (gameWidth/2 + 100, 0)), Vertex (Vector2f (gameWidth/2 - 100, gameHeight))
	};
	
	// bat1 for player 1 on the left side of the line
	// bat2 for player 2 on right side of the line
	Bat bat1(player1); 
	Bat bat2(player2);

// Create the ball, starting in the center of the window
	Ball ball(gameWidth/2 + 10, gameHeight / 2);

// Creates the players' scores on the board
// Starting at zero
// Player 1 is on the left
// Player 2 is on the right
	int player1S = 0; 
	int player2S = 0; 

// Creates boolean game over value
// It is set to false because the game has just started
// Eventually, when the first player scores 3 pts and wins, its set to true.
	bool gameOver = false;

	// Create a text obj
	// Font is "28 Days Later" from freefont website
	// Also create size and color of font
	Text hud; 
	Font font;
	font.loadFromFile("28 Days Later.ttf");

	hud.setCharacterSize(183);
	hud.setColor(Color::White);

	// Now set the font
	hud.setFont(font);

	// Let's create the board
	// Color is bright red
	// Bat, ball, and text is formed onscreen and displayed
	window.clear(Color(205, 10, 18, 255));
	window.draw(bat1.getFormation());
	window.draw(bat2.getFormation());
	window.draw(ball.getShape());
	window.draw(hud);
	window.draw(line, 2, Lines);
	window.display();

	// Start Game 

	// Set framerate to 50 fps
	window.setFramerateLimit(50);

	// While the game is inplay
	while (window.isOpen()) {

		// First create an event in which window closes, the game ends 
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Determines keyboard controls for players
		// Player 1 handles keys W as Up and S as Down
		// Player 2 gets the key pad
		// If those respective keys are pressed
		// then the paddles move in that direction
		// If the escape key is pressed, then the game quits and closes
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			bat1.moveUp();
		} else if (Keyboard::isKeyPressed(Keyboard::S)) {
			bat1.moveDown();
		} else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			bat2.moveUp();
		} else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			bat2.moveDown();
		} else if (Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		
		// Gets position for player points
		bool player1Pt = ball.getPosition().left + 40 > gameWidth;
		bool player2Pt = ball.getPosition().left < 0;

		// Compares player points
		// If one has scoared, they get the point
		// then game continues to next round
		// ball is reset
		if (player1Pt || player2Pt) {
			if (player2Pt) {
				player2S++;
			} else {
				player1S++;
			}
			ball.hitWall();
		}

		// When the ball hits the upper or lower wall
		// get ball position and make sure it is not lesser than 0 (the line)
		// same with bottom wall, creating the bounds with the entire height
		// with consideration to the size of the ball
		bool tWallCollision = ball.getPosition().top < 0;
		bool bWallCollision = ball.getPosition().top > gameHeight - ballSize;

		// If the ball hits either the upper or bottom wall
		// reverse yvelocity so it looks like the pong ball is hitting off the wall
		if (tWallCollision || bWallCollision) {
			ball.hitBall();
		}

		// Create instances where the ball collides with the players bat
		bool ballhitbat1 = ball.getPosition().intersects(bat1.getPosition());
		bool ballhitbat2 = ball.getPosition().intersects(bat2.getPosition());

		// So once this event happens
		// the xvelocity is reverse so it looks like the ball bounces off the players bat
		if (ballhitbat1 || ballhitbat2) {
			ball.hitBat();
		}

		// As long as the game is in play
		// all positions and moves are updated
		if (!gameOver) {
			bat1.update();
			bat2.update();
			ball.update();
		}

		// Scores are updated
		std::stringstream scoreBoard; 

		// Couldnt think of another way to separate playerscores on the board
		// this works though
		scoreBoard << " " << player1S << "            " << player2S;

		hud.setString(scoreBoard.str());

		// Whoever gets to 3 points first, wins!
		if (player1S == 3 || player2S == 3) {

			// Create variable int winnerNumber and set to 0.
			int winnerNumber = 0;

			// Whichever player wins will project them as winner on screen
			if (player1S == 3) {
				winnerNumber = player1;
			}

			if (player2S == 3) {
				winnerNumber = player2;
			}

			// Create another stringsterm 
			// in place of scoreBoard
			// will pronounce winner on screen
			std::stringstream wiNNer;
			wiNNer << "PLAYER " << winnerNumber << " WINS! ";

			// Now its Game Over
			gameOver = true;
			if (gameOver) {
				hud.setString(wiNNer.str());
			}
		}

		// Now redraw everything
		// If this isn't placed at code end
		// then game will not work
		window.clear(Color(205, 10, 18, 255));
		window.draw(bat1.getFormation());
		window.draw(bat2.getFormation());
		window.draw(ball.getShape());
		window.draw(hud);
		window.draw(line, 2, Lines);
		window.display();
	}

	return EXIT_SUCCESS;
} 