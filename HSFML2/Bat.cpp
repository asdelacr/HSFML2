#include "stdafx.h"
#include "Bat.h"

// Give Player 1 and 2 their respective values
#define player1 1
#define player2 2

#define gameWidth 1100
#define gameHeight 600

// Define how long and wide the bats will be
#define batHeight 120
#define batWidth 40

using namespace sf;

Bat::Bat(int definePlay) {

	// Defines which player is which
	player = definePlay;

	// Player 1 is positioned on the left side
	// a little bit off the left wall
	// hence why the value of its x coord is + 10
	if (player == player1) {
		position.x = 10;
	} else {
	// otherwise, it is the other Player
	// whose bat is on the opposite side
		position.x = gameWidth - batWidth - 10;
	}

// Both players start at the same height
// which is in the middle of the walls
	position.y = gameHeight / 2;

// now sets there position
	batshape.setSize(Vector2f(batWidth, batHeight));
	batshape.setPosition(position);
}

// Gets position and Form
FloatRect Bat::getPosition() {
	return batshape.getGlobalBounds();
}

RectangleShape Bat::getFormation() {
	return batshape;
}

// Move Bat up and down by increasing or decreasing speed
// depending where your going
void Bat::moveUp() {
	position.y -= batspeed;
}

void Bat::moveDown() {
	position.y += batspeed;
}

// update all
void Bat::update() {
	batshape.setPosition(position);
}