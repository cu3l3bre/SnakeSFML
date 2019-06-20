//**************************************************************************************************
/*!
 @file           level.h
 @brief          Declaration of Level class
 @date           17.06.2019
 @author         Daniel Schmunkamp
 */
 //**************************************************************************************************

#pragma once

#include "point.h"
#include <vector>
#include <fstream>
#include <string>
#include "time.h"
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>

#define GAMESIZE_XY 500

// Class Level
class Level
{
public:

	Snake snake;	// Object of snake

	Point foodLocation;		// Location where the food is
	bool foodOnField;		// State if food is on the field or not
	int foodCount;			// Counter how much food has been eaten

	bool gameRunning;		// State if the game is running or not
	bool gameOver;			// State if the game is over or not
	int score;				// Achieved score
	
	std::string pathToHighscoreFile;		// Location where the highscore file is stored
	std::string oneLine;					// Line that has been read from the file
	std::vector<std::string> fileContent;	// List of the lines contained in the file

	int currentHighscoreScore;				// Current highscore listet in the file
	std::string currentHighscoreDate;		// Current date listet in the file

	// Some help variables
	std::string scoreString;
	std::string foodString;
	std::string timeElapsedString;
	std::string yearString;
	std::string monthString;
	std::string dayString;
	std::string hourString;
	std::string minuteString;

	std::string currentHighscoreScoreString;
	std::string currentHighscoreDateString;
	

	sf::Time timeElapsed;			// Time elapsed from start to GameOver
	float timeElapsedSeconds;		// Time elapsed in seconds
	sf::Clock clock;				// Used to measure the time

	// Some variables to get the current date and time when the game is over
	tm nowLocal;
	time_t timeNow;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;


	int circleRadius;		// Radius of the circle shape
	int stepSize;			// Stepsize how many points/ steps will make in one cycle
	int offsetOrigin;		// Offset to the origin where the drawing of a shape will start


	sf::CircleShape food;	// Object for the food which is represented by a circle

	sf::Vector2f rectangleSize;						// Size for one boundary, which is a rectangle (indeed its a square)
	sf::RectangleShape boundary;					// Object for a boundary
	std::vector<sf::RectangleShape> boundaries;		// List of rectangle shapes => boundaries

	sf::FloatRect bounds;	// Used to get the bounds of the used texts to place them in the middle of the window

	// Some text objects for showing texts in the main window
	sf::Text txt_instrcution;
	sf::Text txt_instrcution2;
	sf::Text txt_instrcution3;
	sf::Text txt_gameOver;
	sf::Text txt_playtimeFood;
	sf::Text txt_totalScore;
	sf::Text txt_date;
	sf::Text txt_currentHighScoreScore;
	sf::Text txt_currentHighScoreDate;
	sf::Text txt_newHighScoreAchieved;


	Level();			// Constructor
	Level(sf::Font*);	// Constructor with has the fonts as paramter
	~Level();			// Destructor

	// Methods
	void createBoundaries();		// Creates the boundaries that limit the field
	void checkGameOver();			// Checks if the GameOver condition is satisfied
	void generateFood();			// Places food on the field
	void eatFood();					// Lets the snake eat food and grow
	void checkSnakeAteFood();		// Checks if the snake ate the food
	void calculateStats();			// Calculates some stats after the game is over
	void showStats();				// Prints out the stats in the console 
	void prepareStats();			// Prepares the stats to show them in the main window
	void prepareCurrentHighscore();	// Prepares the current highscore to show it in the main window
	void readHighScoresFromFile();	// Reads the current highscore stats from the file
	void writeHighScoresToFile();	// Writes the current highscore stats to the file
};