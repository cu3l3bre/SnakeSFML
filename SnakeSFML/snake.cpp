//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#include "snake.h"


// Constructor

Snake::Snake()
{
	snakeLength = 6;

	location.row = 275;
	location.col = 275;


	head.setRadius(5.f);
	head.setFillColor(sf::Color::Red);

	body.setRadius(5.f);
	body.setFillColor(sf::Color::Green);


	// Generate the head and body for the snake in a vertical line
	for (int i = 0; i < snakeLength; i++)
	{
		snakePoints.push_back(location);
		location.row += 10;
	}

	// StartDirection in which the snake will move at the beginning
	direction = SnakeUp;
}


// Destructor
Snake::~Snake(){}




// Copy point values of the snake from top to bottom
// Index 0 will be the new field when the snake has moved
void Snake::updateSnake()
{
	// Removing old values wheres the snake has been
	snakebody.clear();

	for (int i = (snakePoints.size() - 1); i > 0; i--)
	{
		snakePoints[i] = snakePoints[i - 1];

		// Sets the drawing origin where the seperat body parts are located
		body.setPosition(snakePoints[i].col - 5, snakePoints[i].row - 5);
		snakebody.push_back(body);
	}
}




// set direction for snake
void Snake::setSnakeDirection()
{
	// write new point vlaue in 0
	switch (direction)
	{
	case SnakeUp:		snakePoints[0].row -= 10; break;
	case SnakeRight:	snakePoints[0].col += 10; break;
	case SnakeDown:		snakePoints[0].row += 10; break;
	case SnakeLeft:		snakePoints[0].col -= 10; break;
	default:break;
	}


	// Set the drawing origin for the head of the snake 
	// since the head has a radius of 5, we have to -5 the get to the upper left corner
	head.setPosition(snakePoints[0].col - 5, snakePoints[0].row - 5);

}