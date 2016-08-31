#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Bat {

private:

	Vector2f position;

	// Use RectangleShape for batShape
	RectangleShape batshape;

	// Create how fast bat can move
	// Put it similar to ball speed
	const float batspeed = 7.0f;

public:

	// Create both players Bats and Constructors
	int player;
	Bat (int definePlay); 

	// Use function getPosition in main function 
	// to find when ball hits the bat
	FloatRect getPosition();

	// Use same function from before
	// gets form of bats
	RectangleShape getFormation(); 

	// Functions that move paddles
	void moveUp(); 
	void moveDown(); 

	// Use func to update where everything moves, is,..
	void update();
};
