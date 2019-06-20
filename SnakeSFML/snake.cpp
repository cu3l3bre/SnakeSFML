//**************************************************************************************************
/*!
 @file           snake.cpp
 @brief          Methods for Snake class
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************

#include "snake.h"

//--------------------------------------------------------------------------------------------------
//! @brief     	Constructor of Snake class
//--------------------------------------------------------------------------------------------------
Snake::Snake()
{
	circleRadius = STEPSIZE / 2;
	stepSize = STEPSIZE;
	offsetOrigin = STEPSIZE / 2;

	snakeLength = 3;

	location.row = ((stepSize / 2) + (stepSize * 10));
	location.col = ((stepSize / 2) + (stepSize * 10));

	head.setRadius(circleRadius);
	head.setFillColor(sf::Color::Red);

	body.setRadius(circleRadius);
	body.setFillColor(sf::Color::Green);


	// Generate the head and body for the snake in a vertical line
	for (int i = 0; i < snakeLength; i++)
	{
		snakePoints.push_back(location);
		location.row += stepSize;
	}

	// StartDirection in which the snake will move at the beginning
	direction = SnakeUp;
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Destructor of Snake class
//--------------------------------------------------------------------------------------------------
Snake::~Snake(){}


//--------------------------------------------------------------------------------------------------
//! @brief     	Copy point values of the snake from top to bottom
//! @brief     	Index 0 will be the new field when the snake has moved
//--------------------------------------------------------------------------------------------------
void Snake::updateSnake()
{
	// Removing old values wheres the snake has been
	snakebody.clear();

	for (int i = (snakePoints.size() - 1); i > 0; i--)
	{
		snakePoints[i] = snakePoints[i - 1];

		// Sets the drawing origin where the seperat body parts are located
		body.setPosition(snakePoints[i].col - offsetOrigin, snakePoints[i].row - offsetOrigin);
		snakebody.push_back(body);
	}
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Sets direction for snake
//--------------------------------------------------------------------------------------------------
void Snake::setSnakeDirection()
{
	// Write new point value in 0
	switch (direction)
	{
	case SnakeUp:		snakePoints[0].row -= stepSize; break;
	case SnakeRight:	snakePoints[0].col += stepSize; break;
	case SnakeDown:		snakePoints[0].row += stepSize; break;
	case SnakeLeft:		snakePoints[0].col -= stepSize; break;
	default:break;
	}

	// Set the drawing origin for the head of the snake 
	head.setPosition(snakePoints[0].col - offsetOrigin, snakePoints[0].row - offsetOrigin);
}


//--------------------------------------------------------------------------------------------------
//! @brief     	Check for Overflow if the new direction has been set
//--------------------------------------------------------------------------------------------------
void Snake::checkDirectionOverflow()
{
	if (direction == -1)
	{
		direction = 3;
	}
	else if (direction == 4)
	{
		direction = 0;
	}
}