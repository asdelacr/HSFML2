#pragma once
#include <SFML/Graphics.hpp>

// Create size of ball
#define ballSize 20

using namespace sf;

class Ball {

private:

	// Get position and form
	Vector2f position;
	RectangleShape ballform;

	// Create x and y velocities 
	// Different values so movement of ball 
	// is not exactly even along the grid
	float xVelocity = 5.0f;
	float yVelocity = 4.0f;

public:

	Ball(float startX, float startY); 

	// Gets position and shape
	FloatRect getPosition(); 
	RectangleShape getShape(); 

	float getXVelocity(); 

    // Determines if the ball hit the wall
	// Gives player point
	void hitWall();

	// Function alters velocity to change direction of ball
	void hitBall(); 

	// alters position of ball
	void hitBat(); 

	// Updates all
	void update();
};
