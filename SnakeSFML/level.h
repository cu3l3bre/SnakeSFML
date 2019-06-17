//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "point.h"
#include <vector>
#include "snake.h"


#define EMPTYFIELD char(0);
#define BOUNDARY '#';
#define SNAKEHEAD 'X';
#define SNAKEBODY '0';
#define FOOD char(148);

using namespace std;

class Level
{
protected:



public:

	Level();
	Level(int, int);
	~Level();

	int rows = 20;
	int cols = 20;
	int points;
	//vector<int> levelPoints;
	char levelPoints[20][20];
	Snake snake;


	Point foodLocation;
	bool foodOnField = false;
	int foodCount;
	double score;


	time_t timeElapsed;
	tm nowLocal;
	time_t timeNow;
	time_t gameStartTime;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;


	// Getter

	// Setter


	// Methods

	void drawBoundaries();
	void updateLevel();

	void drawLevel();
	bool checkGameOver();

	void generateFood();
	void eatFood();

	void calculateScore();
};