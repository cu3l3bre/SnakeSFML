//**************************************************************************************************
/*!
 @file           snake.h
 @brief          Declaration of Snake class
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************

#pragma once

#include "point.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// For now choose 10 or 20
#define STEPSIZE 20

// Enum for movement directions for the snake
enum SnakeDirection
{
	SnakeUp,
	SnakeRight,
	SnakeDown,
	SnakeLeft
};

// Note to SnakeDirection
// if we do +1 on each direction, we cycle through it clockwise
// if we do -1 on each direction, we cycle through it counterclockwise
// but need to pay attention if we are on 0 and do -1 , that would be -1 which would equal 3
// same is when direction is 3 and we do +1, that would be 4 , in that case it would be 0
// so we have to check for that "overflow"

//							SnakeUp = 0
//
//		SnakeLeft = 3							SnakeRight = 1
//
//							SnakeDown = 2


// Class Snake
class Snake
{
public:

	int snakeLength;	// Length of the snake
	int direction;		// Direction in which the snake moves (0 = up, 1 = right; 2 = down , 3 = left)

	Point location;		// Location where the snake head is

	std::vector<Point> snakePoints;	// Locations where the body parts of the snake are

	int circleRadius;		// Radius of the shape, which represents the head and one body part
	int stepSize;			// Defines how much points move with one step
	int offsetOrigin;		// Defines the offset, from the center of a shape, used for start drawing point

	sf::CircleShape head;	// CircleShape for the head
	sf::CircleShape body;	// CircleShape for one body part

	std::vector<sf::CircleShape> snakebody;		// vector of body parts (needed for drawing)


	Snake();	// Constructor
	~Snake();	// Desructor
	
	// Methods 
	void updateSnake();				// Updates the snake values after each step
	void setSnakeDirection();		// Sets the Direction in which the snake will move
	void checkDirectionOverflow();	// Checks for an overflow in the directions (can happen at direction 0 and 3)
};