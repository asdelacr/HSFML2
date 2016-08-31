#include "stdafx.h"
#include "Ball.h"

#define gameWidth 1100
#define gameHeight 600

//using namespace sf;

Ball::Ball(float startX, float startY) {

	// Initially positions ball
	position.x = startX;
	position.y = startY;

	// Sets ball size and position
	ballform.setSize(sf::Vector2f(ballSize, ballSize));
	ballform.setPosition(position);
}

// Returns FloatRect to calling code
// helps for collision detection in main code
FloatRect Ball::getPosition() {
	return ballform.getGlobalBounds();
}

// Returns copy of RectangleShape to be drawn in window
RectangleShape Ball::getShape() {
	return ballform;
}

float Ball::getXVelocity() {
	return xVelocity;
}

// When ball hits upper/lower wall 
// Makes y velocity value negative to give 
// appearance it bumped into something
void Ball::hitBall() {
	yVelocity = -yVelocity;
}

// Similar to hitBall, only change in x velocity
void Ball::hitBat() {

	// Multiply velocity by 10 to prevent ball from 
	// completely stopping, changing framerate
	position.x -= (xVelocity * 10); 
	xVelocity = -xVelocity;
}

// Occurs when ball passes player and hits opposing side
// detects wall hit, point is given to scorer
// ball is reset to the middle of screen and new round starts
void Ball::hitWall() {
	position.x = gameWidth / 2;
	position.y = gameHeight / 2;
}

// Update positions
void Ball::update() {
	position.y += yVelocity;
	position.x += xVelocity;
	ballform.setPosition(position);
}
